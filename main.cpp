#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#ifdef __GNUC__
#define __rdtsc __builtin_ia32_rdtsc
#else
#include <intrin.h>
#endif

typedef unsigned long long u64;

using namespace std;
typedef bitset<8> BYTE;
void hextobin(string hex,vector<char> & m, vector<char> & l,vector<char> & r){
    int i=0;
    while (hex[i] != '\0'){
        switch(hex[i])
        {
            case '0':
                m.push_back('0');m.push_back('0');m.push_back('0');m.push_back('0');
                break;
            case '1':
                m.push_back('0');m.push_back('0');m.push_back('0');m.push_back('1');
                break;
            case '2':
                m.push_back('0');m.push_back('0');m.push_back('1');m.push_back('0');

                
                break;
            case '3':
                m.push_back('0');m.push_back('0');m.push_back('1');m.push_back('1');
            
               
                break;
            case '4':
                m.push_back('0');m.push_back('1');m.push_back('0');m.push_back('0');

               
                break;
            case '5':
                m.push_back('0');m.push_back('1');m.push_back('0');m.push_back('1');
        
                
                break;
            case '6':
                m.push_back('0');m.push_back('1');m.push_back('1');m.push_back('0');
         
                break;
            case '7':
                m.push_back('0');m.push_back('1');m.push_back('1');m.push_back('1');
          
                
                break;
            case '8':
                m.push_back('1');m.push_back('0');m.push_back('0');m.push_back('0');
             
               
                break;
            case '9':
                m.push_back('1');m.push_back('0');m.push_back('0');m.push_back('1');
       
                break;
            case 'A':
            case 'a':
                m.push_back('1');m.push_back('0');m.push_back('1');m.push_back('0');
              
                break;
            case 'B':
            case 'b':
                m.push_back('1');m.push_back('0');m.push_back('1');m.push_back('1');
               // m.push_back("1011");
               
                break;
            case 'C':
            case 'c':
                m.push_back('1');m.push_back('1');m.push_back('0');m.push_back('0');

          
                break;
            case 'D':
            case 'd':
                m.push_back('1');m.push_back('1');m.push_back('0');m.push_back('1');
    
         
                break;
            case 'E':
            case 'e':
                m.push_back('1');m.push_back('1');m.push_back('1');m.push_back('0');

                
                break;
            case 'F':
            case 'f':
                m.push_back('1');m.push_back('1');m.push_back('1');m.push_back('1');
         
               
                break;
            defaumt:
                break;
        }
        i++;
    }
    for (int i = 0; i < 64; i++) {
        if(i<32) l.push_back(m[i]);
        else r.push_back(m[i]);
    }
}

vector<string> subkeys(vector<char>  key){
    string k_="",k__="";
    string C0="";
    string D0="";
    string C_new="";
    string D_new="";
    string CD="";
    vector<pair<string,string>> keys;
    vector<string> sub_keys;
    int Left_shifts[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1}; 
        int PC_1[56] = {
              57,   49,    41 ,  33,    25,    17,    9,
               1,   58,    50,   42,    34,    26,   18,
              10,    2,    59,   51,    43,    35,   27,
              19,   11,     3,   60,    52,    44,  36,
              63,   55,    47,   39,    31,    23,   15,
               7,   62,    54,   46,    38,   30,   22,
              14,    6,    61,   53,    45,    37,   29,
              21,   13,     5,   28,    20,    12,    4
        };
    
    for (int i=0;i<56;i++){
        k_ += key[PC_1[i]-1];
    }
    C0 = k_.substr(0,28);
    D0 = k_.substr(28,56);
    //cout << C0.substr(0,28) << endl; 
    keys.push_back(make_pair(C0, D0));
    for (int i = 0;i<16;i++){
        if(Left_shifts[i]==1){
            C_new = C0.substr(1,28) + C0[0];
            D_new = D0.substr(1,28) + D0[0];
        }
        else{
            C_new = C0.substr(2,28) + C0[0] + C0[1];
            D_new = D0.substr(2,28) +D0[0]+D0[1];
        }
        
        C0=C_new;D0=D_new;
        keys.push_back(make_pair(C0, D0));
        //cout << "C: " <<C0 << "   D: "<< D0<<endl;
    }
    
    
    int  PC_2[56]={

                 14 ,   17,   11,    24,     1,    5,
                  3,    28,   15,     6,    21,   10,
                 23,    19,   12,     4,    26,    8,
                 16,    7,   27,    20,   13,    2,
                 41,    52,   31,    37,    47,   55,
                 30,    40,   51,    45,    33,   48,
                 44,    49,   39,    56,    34,   53,
                 46,   42,   50,    36,    29,   32
    };
    for (int i=1;i<17;i++){
        CD = keys[i].first + keys[i].second;
        for (int j=0;j<56;j++)
            k__ += CD[PC_2[j]-1];
        sub_keys.push_back(k__);
        k__="";
    }
    return sub_keys;
}

u64 func(u64 R,u64 k){
    u64 out_final =0;
    u64 out_final2=0;
    u64 E_R =0;
       int E_bit[48]= {
                 32,     1,    2,     3,     4,    5,
                  4 ,    5,    6,     7,     8,    9,
                  8  ,   9,   10,    11,    12,   13,
                 12 ,   13,   14,    15,    16,   17,
                 16 ,   17,   18,    19,    20,   21,
                 20 ,   21,   22,    23,    24,   25,
                 24 ,   25,   26,    27,    28,   29,
                 28 ,   29,   30,    31,    32,    1,
       };
    int P_mat[32]={
             16,   7,  20,  21,
             29,  12, 28,  17,
              1,  15,  23,  26,
              5,  18,  31,  10,
              2,   8,  24,  14,
             32,  27,  3, 9,
             19,  13,  30,   6,
             22,  11,   4,  25,
    };


       int Ss[8][64] ={
        {
             14,  4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7 ,
              0, 15,   7,  4,  14,  2,  13,  1,  10,  6,  12, 11,   9,  5,   3,  8 ,
              4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0 ,
             15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13 
        },
        {
             15,  1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10 ,
              3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5 ,
              0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15 ,
             13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9 
        },
        {
             10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8 ,
             13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1 ,
             13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7,
              1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12 
        },
        {
              7, 13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15 ,
             13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9 ,
             10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4 ,
              3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14 
        },
        {
              2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9 ,
             14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6 ,
              4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14 ,
             11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3 
        },
        {
             12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11 ,
             10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8 ,
              9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6 ,
              4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13 
        },
        {
              4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1 ,
              13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6 ,
              1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2 ,
              6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12 
        },
        {
             13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7 ,
              1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2 ,
              7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8 ,
              2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11 
        }
    };

    //printf("R: %016llX \n",R);
    for(int i=0;i<48;++i)
          E_R|=(R>>(32-E_bit[48-1-i])&1)<<i;
    //printf("E_R: %016llX \n",E_R);
    // E_R [48] = 0x00007A15557A1555;;;;;;
    u64 out = E_R ^ k;
     //printf("K: %016llX \n",out);

    for (int i=0;i<8;i++){
    u64 idx = out>> (7-i)*6 & 0x3F;
    idx = idx>>1&15|(idx&1)<<4|idx&0x20;
    int Q = Ss[i][int(idx)];
    out_final2 |= Q << (7-i)*4;
    }

    //out_final2 = 0x00000005c82B597;;;
    for(int i=0;i<32;++i)
        out_final |=(out_final2>>(32-P_mat[32-1-i])&1)<<i;
    return out_final;
}




u64 data_enc(u64 data,vector<u64> k,int is_enc){
        u64 final = 0;
        u64 IP_out = 0;
        int IP[64]={
        58,    50,   42,    34,    26,   18,    10,    2,
        60,    52,   44,    36,    28,   20,    12,    4,
        62,    54,   46,    38,    30,   22,    14,    6,
        64,    56,   48,    40,    32,   24,    16,    8,
        57,    49,   41,    33,    25,   17,     9,    1,
        59,    51,   43,    35,    27,   19,    11,    3,
        61,    53,   45,    37,    29,   21,    13,    5,
        63,    55,   47,    39,    31,   23,    15,    7
         };
        for(int i=0;i<64;++i)
            IP_out|=(data>>(64-IP[i])&1)<<64-(i+1);
            
        
        
        
        int L0 = IP_out >> 32;
        int R0 = IP_out & 0x00000000FFFFFFFF;
        u64 R=R0;
        u64 L=L0;
       
        u64 func_out = 0;
        u64 new_R,new_L;
        new_R = func(u64(R),k[0]);

        
        if (is_enc==0){ //enc
        for (int i=0;i<16;i++){
                   new_R = L ^ func(u64(R),k[i]);
                   new_L = R;
                   R = new_R; L=new_L;
            }
        }
        else{       ///dec
              for (int i=0;i<16;i++){
                   new_R = L ^ func(u64(R),k[16-i-1]);
                   new_L = R;
                   R = new_R; L=new_L;
            }
        }
        u64 out1 = (R<<32)|(L&0x00000000FFFFFFFF);
         int IP_1[64] = {
            40,     8,   48,    16,    56,   24,    64,   32,
            39,     7,   47,    15,    55,   23,    63,   31,
            38,     6,   46,    14,    54,   22,    62,   30,
            37,     5,   45,    13,    53,   21,    61,   29,
            36,     4,   44,    12,    52,   20,    60,   28,
            35,     3,   43,    11,    51,   19,    59,   27,
            34,     2,   42,    10,    50,   18,    58,   26,
            33,     1,   41,     9,    49,   17,    57,   25   };
            

        for(int i=0;i<64;++i)
          final |=(out1>>(64-IP_1[64-1-i])&1)<<i;
          
        return final;
}  

int main(int argc, char** argv)
{
    u64 output=0;
    string data_str = argv[2];
    string key = argv[3];
    string op = argv[1];
    
    std::string::size_type sz = 0;
    u64 data = stoull(data_str,&sz,16);
    
    int op_dec = 0;
    if(op=="encrypt") op_dec= 0;
    else if (op=="decrypt") op_dec = 1;
    
    vector<char> k;
    vector<char> k_l;
    vector<char> k_r;
    vector<string> keys;
    vector <u64> keys_u64;
    hextobin(key,k,k_l,k_r);
    keys = subkeys(k);
    for (int i=0;i<16;i++){
    std::string::size_type sk = 0;
    keys_u64.push_back(stoull(keys[i],&sk,2));
    }
    
    long long t1 = __rdtsc();   
    
    output = data_enc(data,keys_u64,op_dec);


    long long t2 = __rdtsc();
    if(op_dec==0)
    printf("cipher: %016llX \n",output);  
    else
    printf("plain: %016llX \n",output);  
    printf("cycles: %lld", t2-t1);
    return 0;
}


