//include
//------------------------------------------
#include <vector>
#include<iostream>
#include<math.h>
#include<map>
using namespace std;


#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;




template<class T>
class SegTree{
    private:

    vector<T> node;
    

    public:
    int Size;//葉のサイズ
    T initializer;//配列の初期値
    
    SegTree(){}
    
    SegTree(int Size_ , T initializer_){
        
        init(Size_,initializer_);

    }

    void init(int S , T I){
        initializer = I;
        int k = log2(S) + 2;

        vector<T>((1<<k),initializer).swap(node);
        Size = (1<<(k-1));//葉のサイズ
    }


    /*
        区間に対する演算 ... + , xor や maxなどができる
    */
    T merge(T a, T b){
        //自分で指定..他にも変更すべき場所があるので注意
        return a+b;
    }


    /*
        葉から根に登りながら更新
        mergeの種類によって編集しないといけない
    */
    void update(int index , T val){
        if(index < 0 || index >=Size)return;

        index += Size;
        T prev = node[index];
        node[index] = val;
        T dif = val - prev;
        while(index/2 > 0){
            index/=2;
            node[index] = merge(node[index*2] , node[index*2+1]);
        }

    }



    /*
        [lef,rig)の半開区間について,木の頂点:SubRootが根となる部分木が覆う区間について調べる。

    */
    T query(int lef , int rig , int SubRoot = 1 , int SubTreeLeft = 0 , int SubTreeRight = -1){
        if(SubRoot == 1)SubTreeRight = Size;

        
        if(rig <= SubTreeLeft){
            //区間が被っていない
            return 0;
        }else if(lef >=SubTreeRight){
            //区間が被っていない
            return 0;
        }else if(  lef <= SubTreeLeft &&  SubTreeRight <= rig ){
            //SubRootを根とする部分木の範囲が、取得したい範囲に完全に含まれている-> node[SubRoot]の値をreturn
            return node[SubRoot];
        }else{
            //SubRootの右の根と左の根に降りて、再度調べる
            int border = (SubTreeLeft+SubTreeRight)/2;
            return merge( query(lef,rig,SubRoot*2,SubTreeLeft,border) , query(lef,rig,SubRoot*2+1,border,SubTreeRight) );
        }
    }



};



int main(){
    
    long long n , q;
    cin >> n >> q;
    SegTree<long long> S(n,0);
    while(q--){
        int c ;
        long long x , y;
        cin >> c >> x >> y;
        if(c==0){
            S.update(x,S.query(x,x+1)+y);
        }else{
            cout << S.query(x,y+1) << endl;
        }
    }
 
 
 
 
    return 0;
}
 
 
 



