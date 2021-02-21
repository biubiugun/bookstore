#include "unrolledlist.h"

element & element::operator=(const element &obj) {
    if(key != obj.key){
        offset = obj.offset;
        strcpy(key,obj.key);
    }
    return *this;
}

element::element(const string &the_key, int the_offset) {
    strcpy(key,the_key.c_str());
    offset = the_offset;
}

element::element(const element &obj) {
    strcpy(key,obj.key);
    offset = obj.offset;
}


block::block():pre(-1),nxt(-1),num(0) {};

unrolledlist::unrolledlist(string file) {
    strcpy(filename,file.c_str());
}

void unrolledlist::split(int offset) {
    fstream in,out;
    out.open(filename,ios::in | ios::out | ios::binary);
    in.open(filename,ios::in | ios::binary);
    if(!out || !in)throw("error");
    block bigger,s1,s2;
    in.seekg(offset);
    in.read(reinterpret_cast<char*>(&bigger),sizeof(block));
    for(int i = 0; i < bigger.num; ++i){
        if(i < 150){
            s1.elementarray[i] = bigger.elementarray[i];
        }else{
            s2.elementarray[i - 150] = bigger.elementarray[i];
        }
    }
    s1.num = 150;
    s2.num = bigger.num - 150;
    in.seekg(0,ios::end);
    int new_offset = in.tellg();
    if(bigger.nxt >= 0){
        out.seekp((sizeof(int) + bigger.nxt));
        out.write(reinterpret_cast<char*>(&new_offset),sizeof(int));
    }
    s1.pre = bigger.pre;
    s2.nxt = bigger.nxt;
    s1.nxt = new_offset;
    s2.pre = offset;
    out.seekp(offset);
    out.write(reinterpret_cast<char*>(&s1),sizeof(block));
    out.seekp(new_offset);
    out.write(reinterpret_cast<char*>(&s2),sizeof(block));
    in.close();
    out.close();
}

void unrolledlist::merge(int offset1, int offset2) {
    fstream in,out;
    out.open(filename,ios::in | ios::out | ios::binary);
    in.open(filename,ios::in | ios::binary);
    if(!out || !in)throw("error");
    block s1,s2;
    in.seekg(offset1);
    in.read(reinterpret_cast<char*>(&s1),sizeof(block));
    in.seekg(offset2);
    in.read(reinterpret_cast<char*>(&s2),sizeof(block));
    s1.nxt = s2.nxt;
    for(int i = 0;i < s2.num; ++i){
        s1.elementarray[i + s2.num] = s2.elementarray[i];
    }
//    bigger.pre = s1.pre;
//    bigger.nxt = s2.nxt;
//    bigger.num = s1.num + s2.num;
    if(s2.nxt > 0){
        out.seekp(s2.nxt + sizeof(int));
        out.write(reinterpret_cast<char*>(&offset1),sizeof(int));
    }
    out.seekg(offset1);
    out.write(reinterpret_cast<char*>(&s1),sizeof(block));
    in.close();
    out.close();
}

void unrolledlist::addElement(element &a) {
    fstream in,out;
    out.open(filename,ios::in | ios::out | ios::binary);
    in.open(filename,ios::in | ios::binary);
    if(!out || !in)throw("error");
    int block_num;
    in.seekg(0,ios::end);
    block_num = in.tellg();
    if(block_num == 0){
        out.seekp(0);
        block tmp;
        out.write(reinterpret_cast<char*>(&tmp),sizeof(block));
    }
    int now = 0;
    int next = nxt_offset(now);
    while(next != -1){
        block temp1;
        in.seekg(next);
        in.read(reinterpret_cast<char*>(&temp1),sizeof(block));
        if(temp1.elementarray[0] < a)break;
        now = next;
        next = nxt_offset(now);
    }
    int loc = -1,judge = 0,j = 0;
    block temp2;
    in.seekg(now);
    in.read(reinterpret_cast<char*>(&temp2),sizeof(block));
    for(auto &i : temp2.elementarray){
        if(a < i){
            loc = j;
            judge = 1;
            break;
        }
        ++j;
    }
    if(judge == 0)loc = temp2.num;
    for(int i = temp2.num;i > loc; --i){
        temp2.elementarray[i] = temp2.elementarray[i - 1];
    }
    ++temp2.num;
    temp2.elementarray[loc] = a;
    out.seekp(now);
    out.write(reinterpret_cast<char*>(&temp2),sizeof(block));
    in.close();out.close();
    if(temp2.num >= 270)split(now);
}

void unrolledlist::deleteElement(element &a) {
    fstream in,out;
    out.open(filename,ios::in | ios::out | ios::binary);
    in.open(filename,ios::in | ios::binary);
    if(!out || !in)throw("error");
    int block_num;
    in.seekg(0,ios::end);
    block_num = in.tellg();
    if(block_num == 0)return;
    int now = 0;
    int next = nxt_offset(now);
    while(next != -1){
        block temp1;
        in.seekg(next);
        in.read(reinterpret_cast<char*>(&temp1),sizeof(block));
        if(a < temp1.elementarray[0])break;
        now = next;
        next = nxt_offset(now);
    }
    int loc,judge = 0,j = 0;
    in.seekg(now);
    block temp2;
    in.read(reinterpret_cast<char*>(&temp2),sizeof(block));
    for(auto &i : temp2.elementarray){
        if(strcmp(a.key,i.key) == 0 && a.offset == i.offset){
            judge = 1;
            loc = j;
            break;
        }
        ++j;
    }
    if(judge == 0)return;
    for(int i = loc;i < temp2.num - 1; ++i){
        temp2.elementarray[i] = temp2.elementarray[i + 1];
    }
    temp2.num--;
    out.seekp(now);
    out.write(reinterpret_cast<char*>(&temp2),sizeof(block));
    in.seekg(now);
    block temp3;
    in.read(reinterpret_cast<char*>(&temp3),sizeof(block));
    next = temp3.nxt;
    block temp4;
    if(next != -1){
        in.seekg(next);
        in.read(reinterpret_cast<char*>(&temp4),sizeof(block));
    }
    in.close();
    out.close();
    if(temp2.num + temp4.num <= 300 && next != -1 )merge(now,next);
}

void unrolledlist::findElement(string key, vector<int> &area) {
    fstream in,out;
    in.open(filename,ios::in | ios::binary);
    if(!in)throw("error");
    in.seekg(0,ios::end);
    int n = in.tellg();
    if(n == 0){
        out.open(filename,ios::in | ios::out | ios::binary);
        if(!out)throw("error");
        block tmp;
        out.seekp(0);
        out.write(reinterpret_cast<char*>(&tmp),sizeof(block));
        out.close();
        return;
    }
    int now,next,pre_offset = 0;
    now = 0;
    block temp1;
    in.seekg(now);
    in.read(reinterpret_cast<char*>(&temp1),sizeof(block));
    next = temp1.nxt;
    while(next != -1){
        block temp2;
        in.seekg(next);
        in.read(reinterpret_cast<char*>(&temp2),sizeof(block));
        if(strcmp(temp2.elementarray[0].key,key.c_str()) > 0)break;
        else{
            in.seekg(now);
            in.read(reinterpret_cast<char*>(&temp2),sizeof(block));
            if(strcmp(temp2.elementarray[0].key,key.c_str()) < 0){
                pre_offset = now;
            }
            now = next;
            block temp3;
            in.seekg(now);
            in.read(reinterpret_cast<char*>(&temp3),sizeof(block));
            next = temp3.nxt;
        }
    }
    while(true){
        block temp4;
        in.seekg(pre_offset);
        in.read(reinterpret_cast<char*>(&temp4),sizeof(block));
        for(int i = 0; i < temp4.num; ++i){
            if(strcmp(temp4.elementarray[i].key,key.c_str()) == 0){
                area.push_back(temp4.elementarray[i].offset);
            }
        }
        if(pre_offset == next)break;
        pre_offset = temp4.nxt;
    }
    in.close();
}
