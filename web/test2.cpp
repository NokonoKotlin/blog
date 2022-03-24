#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<algorithm>



const long long INF = 1e18;
const long long NINF = 1 - 1e18;
using namespace std;

















/*

    splitした後はmergeを忘れずに！！(それかSplitした頂点のrootを覚えておこう)

    頂点にアクセスしたら、その頂点をsplayするのを忘れるな！！
    頂点をいじったらsplayの後、Updateするのを忘れないで

    Treeの上の操作は、Glaphのデータ構造をを用意して行うのではなく、
    SplayNodeというデータ構造に必要なデータを持たせて、SplayNode間でやり取りさせる.


    rootを頂点とする部分木において{
        split(l,root) := lで分割

        merge(l_root , r_root) := 頂点がl_root ,r_rootであるような部分木を連結

        insert_sub(ind,NODE,root) := ind番目にNODEが挿入される

        Delete_sub(ind ,root) := ind番目を削除(返り値はfirstが新しいroot , secondが削除したNode)

    }
    これらを駆使し、様々な操作を実装可能



*/
template<class T>
class SplayTree{
    public:


    /*
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
            SplayTreeの、Nodeのデータ構造。
            SplayTreeでは、Glaphの配列上で操作のやり取りをするのではなく、
            SplayNodeというデータ構造に持たせたデータでやり取りをする
        ------------------------------------------------------------------------------------------------------------------------------------------------------------   
        ------------------------------------------------------------------------------------------------------------------------------------------------------------

    */

    struct SplayNode{

        SplayNode *parent;//親ノード
        SplayNode *left;//左の子ノード
        SplayNode *right;//右の子ノード

        T Value;//値(普通、頂点には値や重みが割り当てられることが多い)
        T Min,Max,Sum;//部分木のうち、値の最大、最小、和

        int SubTreeSize = 1;//1は初期化値(自分自身)


        SplayNode(){
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            
        }
        SplayNode(T val){
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            Value = val;
            Min = val;
            Max = val;
            Sum = val;
        }


        bool isExist(SplayNode *Nd){
            if(Nd!=nullptr)return true;
            else return false;
        } 



        /*
            ある地点を回転させる
        */
        void rotate(){

            SplayNode *Parent , *GrandParent , *Child;
            Parent = this->parent;
            GrandParent = Parent->parent;

            if(isExist(Parent) == false){
                return;
            }



            //元の親に対する位置で場合分け
            if(Parent->left == this){
                Child = this->right;//Childはnullptrかもしれない
                this->right = Parent;
                Parent->left = Child;

            }else if(Parent->right == this){
                Child = this->left;
                this->left = Parent;
                Parent->right = Child;

            }

            if(isExist(GrandParent)){
                //GrandParentのどちらの辺なのかで場合分け
                if(Parent == GrandParent->left){
                    GrandParent->left = this;

                }else if(Parent == GrandParent->right){
                    GrandParent->right = this;
                    
                }
            }

            //GrandParentがnullptrの場合でも代入OK
            this->parent = GrandParent;


            //親と位置を入れ替えるので
            Parent->parent = this;



            //Childは移動するので。
            if(isExist(Child))Child->parent = Parent;


            /*
                Nodeの持つ情報をupdateしないといけないが、順番に注意！！
                ChildはChild以下の部分木が変化してないので何もしなくてOK
                GrandParentは、部分木の中の順番が変わったけど、集合としては変わってないので何もしなくてOK
                Parentと自分自身(this)は順番が変わって、部分木の内容も変わったので、
                下から　Parent　⇨  this の順番でupdateする
            */
            Parent->update();
            this->update();

            

            return;

        }







        /*
            自分の親から見た自分の位置
            0 -> 親がそもそもいない or 例外の場合
            1 -> 親から見て左の子の場合
            2 -> 親から見て右の子の場合 
        */
        int state(){
            if(isExist(this->parent)== false){
                return 0;
            }else{
                if(this->parent->left == this){
                    return 1;
                }else if(this->parent->right == this){
                    return 2;
                }else {
                    return 0;
                }
            }
        }







        /*
            あるNodeを回転を駆使し一番上まで持っていく
            この時、回転する順番に注意
        */
        void splay(){

            if(isExist(this) == false)return;
            
            while(isExist(this->parent)){
                if(isExist(this->parent->parent)==false){
                    //(自分のGrandParentがいない場合、rotateは一回のみ)
                    this->rotate();
                    return;


                //それ以外の場合、(自分、親、親の親)の位置関係が大事
                }else if(this->state() == this->parent->state()){
                    //GrandParentからの道が(右、右)or (左、左)の場合
                    //GrandParentを一つ下に下ろして、自分を上げる
                    this->parent->rotate();
                    this->rotate();

                }else{
                    //それ以外の場合、単純に自分を2回上に上げれば良い
                    this->rotate();
                    this->rotate();
                }
            }



            return;
        }   






        /*
            サイズなど、Nodeの持っている情報をupdateする(順番大事)
        */
        void update(){
            if(isExist(this) == false)return;
            this->SubTreeSize = 1;
            this->Min = this->Value;
            this->Max = this->Value;
            this->Sum = this->Value;


            if(isExist(this->left)){
                this->SubTreeSize += this->left->SubTreeSize;
                if(this->left->Min < this->Min)this->Min = this->left->Min;
                if(this->left->Max > this->Max)this->Max = this->left->Max;
                this->Sum += this->left->Sum;
            }

            if(isExist(this->right)){
                this->SubTreeSize += this->right->SubTreeSize;
                if(this->right->Min < this->Min)this->Min = this->right->Min;
                if(this->right->Max > this->Max)this->Max = this->right->Max;
                this->Sum += this->right->Sum;

            }

            return;
        }

    };



    /*
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
            ここからやっとSplayTreeに載せる関数たちの出番
            rootを根とする部分木において、
              split(ind,root) , merge(l_root, r_root) , delete_sub(ind,root) , insert_sub()　など
            これらは主にclass内で使われる。
            classの外で使う関数として、
                Delete , insert, RangeSumQuery , shiftなどが想定される
        ------------------------------------------------------------------------------------------------------------------------------------------------------------   
        ------------------------------------------------------------------------------------------------------------------------------------------------------------

    */



    //これは、Nodeを管理する配列のサイズで、木のサイズではない(変更しないので、あらかじめ大きめにとっておく)
    int Size = 0;
    //この木のroot,splitした後はmergeして戻す！！rootが迷子にならないように！！
    SplayNode *Root = nullptr;




    SplayTree(){

    }

    SplayTree(int size_){
  
    }

    bool isExist(SplayNode *Nd){
        if(Nd==nullptr){
            return false;
        }else{
            return true;
        }
    }




    /*
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ここからは、クラス内で動かす関数たちです。俗にいうブラックボックスです。
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    */


    private:







    /*
        rootを根とする部分木において、
        indexを左からの0-indexとすると、

        求めたいindexになるまで降りていく

    */
    SplayNode *getNode(int index , SplayNode *root){
        
        if(isExist(root)==false)return root;
        

        SplayNode *now = root;

        while(1){

            int left_size = 0;
            if(isExist(now->left)){
                left_size = now->left->SubTreeSize;
            } 

            if(index < left_size){
                now = now->left;
            }else if(index == left_size){
                now->splay();
                break;
            }else if(index > left_size){
                now = now->right;
                index = index - left_size-1;
            }

        }


        return now;
    }













    /*
        それぞれ、leftrootとrightrootが根であるような部分木をくっつける

        splitした後、これをしてまたsplitしたものをくっつける
        splitしたまま放置すると分割された木のrootが行方不明になりそう
    */
    SplayNode *merge(SplayNode *leftRoot , SplayNode *rightRoot){

       
        if(isExist(leftRoot) == false)return rightRoot;//右のみあり
        if(isExist(rightRoot) == false )return leftRoot;//左のみあり


        leftRoot = getNode(leftRoot->SubTreeSize-1 , leftRoot);
        leftRoot->right = rightRoot;
        rightRoot->parent = leftRoot;
        leftRoot->update();
        
        return leftRoot;
    }









    /*
         rootを根とする部分木において、
        左からleftnum番目の頂点で左右にsplit。
        splitした後はmergeしないと,splitした木の頂点が行方不明になりそう
    */
    std::pair<SplayNode*,SplayNode*> split(int leftnum, SplayNode *root){

        if(leftnum<=0)return std::make_pair(nullptr , root);

        if(leftnum >= root->SubTreeSize)return std::make_pair(root, nullptr);



        root = getNode(leftnum , root);
        
        SplayNode *leftRoot , *rightRoot;

        leftRoot = root->left; 
        
        rightRoot = root; 

        
        if(isExist(rightRoot))rightRoot->left = nullptr;
        
        if(isExist(leftRoot))leftRoot->parent = nullptr; 
        
        rightRoot->update();


        return std::make_pair(leftRoot,rightRoot);

    }





    /*
         rootを根とする部分木において、
        indexの場所を切り離して、NODEを追加して元に戻す(merge)
    */
    SplayNode  *insert_sub(int index , SplayNode *NODE , SplayNode *root){
        if(isExist(root) == false){
            root=NODE;
            Size=1;
            return root;
        }
        if(Size<index || index<0)return root;

        std::pair<SplayNode*,SplayNode*> Trees = split(index,root);

        SplayNode *leftRoot = Trees.first;
        SplayNode *rightRoot = Trees.second;
        Size++;

        return merge(merge(leftRoot , NODE),rightRoot);
    }









    /*  
        rootを根とする部分木において、
        左からindexの場所を削除して、両端をくっつける
        firstは消したやつ以外をmergeした時のroot
        secondは消したSplayNode
    */
    std::pair<SplayNode*,SplayNode*> Delete_sub(int index , SplayNode *root){
        
        if(isExist(root) == false){
            
            return std::make_pair(root,root);
        }
        if(index<0 || index >= Size){

            return std::make_pair(root,root);
        }
        
        if(Size == 1){

            Size = 0;
            root = nullptr;
            return std::make_pair(nullptr,nullptr);
        }

        root = getNode(index,root);

        SplayNode *leftRoot = root->left;
        SplayNode *rightRoot = root->right;

        if(isExist(leftRoot))leftRoot->parent = nullptr;
        if(isExist(rightRoot))rightRoot->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;

        Size--;
        
        root->update();
        
        return std::make_pair(merge(leftRoot,rightRoot) , root );
    }








    /*
        rootを根とする部分きにおいて、
        0-indexの区間[l,r)を右シフト(右端は左端へ)する
    */
    SplayNode *shift_right_sub(int l , int r , SplayNode *root ){
        r--;//半開区間なので

        std::pair<SplayNode*,SplayNode*> tmp = Delete_sub(r,root);
        root = tmp.first;
        SplayNode *N = tmp.second;

        return insert_sub(l,N,root);

    }



    /*
        rootを根とする部分きにおいて、
        0-indexの区間[l,r)を左シフト(左端は右端へ)する
    */
    SplayNode *shift_left_sub(int l , int r , SplayNode *root ){
        r--;//半開区間なので

        std::pair<SplayNode*,SplayNode*> tmp = Delete_sub(l,root);
        root = tmp.first;
        SplayNode *N = tmp.second;

        return insert_sub(r,N,root);

    }









    /*
        rootを根とする部分木の[l,r)の区間取得クエリ
        modeが 0->Min, 1->Max ,2->Sum 
    */
    std::pair<SplayNode*,T> RangeQuery_sub(int l , int r , int mode , SplayNode *root){

        SplayNode *leftRoot , *centerRoot , *rightRoot; 
        r--;//半開区間なので

        std::pair<SplayNode*,SplayNode*>  tmp = split(r+1,root);
        rightRoot = tmp.second;
        
        tmp = split(l,tmp.first);
        leftRoot = tmp.first;
        centerRoot = tmp.second;

        T ans;
        //modeによって取得する値が違う
        if(mode == 0){
            ans  = centerRoot->Min;
        }else if(mode == 1){
            ans  = centerRoot->Max;
        }else if(mode == 2){
            ans = centerRoot->Sum;
        }else{
            ans = centerRoot->Sum;
        }

        return std::make_pair(merge(merge(leftRoot,centerRoot),rightRoot),ans);
    }


    /*
        SubTreeSize用
    */
    std::pair<SplayNode*,long long> RangeSubTreeSizeQuery_sub(int l , int r , SplayNode *root){

        SplayNode *leftRoot , *centerRoot , *rightRoot;
        r--;//半開区間なので

        std::pair<SplayNode*,SplayNode*>  tmp = split(r+1,root);
        rightRoot = tmp.second;
        
        tmp = split(l,tmp.first);
        leftRoot = tmp.first;
        centerRoot = tmp.second;

        int ans = centerRoot->SubTreeSize;

        return std::make_pair(merge(merge(leftRoot,centerRoot),rightRoot),ans);
    }








    /*
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ここからは、クラスの外で動かす関数たちです。
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    */



     public:



    /*
        木全体のindex番目のNode(値渡し)を取得
    */
    SplayNode get(int index){
        if(index<0 || index>=Size){
            std::cerr<< "index exceeds Size" << std::endl;
            return SplayNode(INF);
        }

        Root = getNode(index,Root);
        Root->update();

        return *(Root);

    }



    void insert(int index , SplayNode *NODE){
        if(index<0 || index> Size)return;

        Root = insert_sub(index , NODE , Root);
        Root->update();

        return;

    }



    /*
        木全体の[l,r)のRMQ
    */
    T RangeMinQuery(int l , int r){
        l = max(0,l);
        r = min(Size,r);
        if(l>=r)return INF;

        std::pair<SplayNode*,T> tmp = RangeQuery_sub(l,r,0,Root);
        Root = tmp.first;
        Root->update();

        return tmp.second;
    }


    /*
        木全体の[l,r)のRMQ
    */
    T RangeMaxQuery(int l , int r){
        l = max(0,l);
        r = min(Size,r);
        if(l>=r)return NINF;

        std::pair<SplayNode*,T> tmp = RangeQuery_sub(l,r,1,Root);
        Root = tmp.first;
        Root->update();

        return tmp.second;
    }



    /*
        木全体の[l,r)のRSQ
    */
    T RangeSumQuery(int l , int r){
        l = max(0,l);
        r = min(Size,r);
        if(l>=r)return 0;

        std::pair<SplayNode*,T> tmp = RangeQuery_sub(l,r,2,Root);

        Root = tmp.first;
        Root->update();

        return tmp.second;
    }


    /*
        木全体の[l,r)の区間の頂点が属する部分木のサイズ
    */
    long long RangeSubTreeSizeQuery(int l , int r){
        l = max(0,l);
        r = min(Size,r);
        if(l>=r)return 0;

        std::pair<SplayNode*,long long> tmp = RangeSubTreeSizeQuery_sub(l,r,Root);
        Root = tmp.first;
        Root->update();

        return tmp.second;
    }


    /*
        木全体で、[l,r)を右シフト(右端は左端へ)
    */
    void shift_right(int l , int r){
        l = max(0,l);
        r = min(Size,r);
        if(l>=r)return;

        Root = shift_right_sub(l,r,Root);
        Root->update();

        return;
    }





    /*
        木全体で、[l,r)を左シフト(左端は右端へ)
    */
    void shift_left(int l , int r){
        l = max(0,l);
        r = min(Size,r);
        if(l>=r)return;

        Root = shift_left_sub(l,r,Root);
        Root->update();

        return;
    }






    /*
        木全体のx番目のvalueをyにする
    */
    void update_val(int x , T y){
    
        Root = getNode(x,Root);
        if(isExist(Root)==false)return;
        Root->Value = y;
        Root->update();

        return;
    }


    /*
        index番目のNodeを消去
    */
    void Delete(int index){
        std::pair<SplayNode*,SplayNode*> tmp = Delete_sub(index,Root);
        
        Root = tmp.first;
        if(isExist(Root) == false )return;
        Root->update();

        return;
    }


    /*
        一列に表示
    */
    void Debug(){
        std::cerr<<"DEBUG:" << std::endl;
        for( int i = 0 ; i < Size ; i++){
            std::cerr<< get(i).Value << " ";
        }
        std::cerr<< std::endl;
    }

    /*
        末尾に追加

    */
    void push_back(T val){
        insert(Size , new SplayNode(val)); 

        return;
    }

    /*
        先頭に追加
    */
    void push_front(T val){
        insert(0 , new SplayNode(val));
        return;
    }





};


















    
/*

    splitした後はmergeを忘れずに！！(それかSplitした頂点のrootを覚えておこう
    )
    頂点にアクセスしたら、その頂点をsplayするのを忘れるな！！
    頂点をいじったらsplayの後、Updateするのを忘れないで


    Treeの上の操作は、Glaphのデータ構造をを用意して行うのではなく、
    SplayNodeというデータ構造に必要なデータを持たせて、SplayNode間でやり取りさせる.
    


    rootを頂点とする部分木において{
        split(l,root) := lで分割

        merge(l_root , r_root) := 頂点がl_root ,r_rootであるような部分木を連結

        insert_sub(ind,NODE,root) := ind番目にNODEが挿入される

        Delete_sub(ind ,root) := ind番目を削除(返り値はfirstが新しいroot , secondが削除したNode)

    }
    これらを駆使し、様々な操作を実装可能


*/
template<class T>
class MyMultiSet{
    public:


    /*
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
            SplayTreeの、Nodeのデータ構造。
            SplayTreeでは、Glaphの配列上で操作のやり取りをするのではなく、
            SplayNodeというデータ構造に持たせたデータでやり取りをする
        ------------------------------------------------------------------------------------------------------------------------------------------------------------   
        ------------------------------------------------------------------------------------------------------------------------------------------------------------

    */

    struct SplayNode{

        SplayNode *parent;//親ノード
        SplayNode *left;//左の子ノード
        SplayNode *right;//右の子ノード

        T Value;//値(普通、頂点には値や重みが割り当てられることが多い)
        T Min,Max,Sum;//部分木のうち、値の最大、最小、和

        int SubTreeSize = 1;//1は初期化値(自分自身)


        SplayNode(){
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            
        }
        SplayNode(T val){
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            Value = val;
            Min = val;
            Max = val;
            Sum = val;
        }


        bool isExist(SplayNode *Nd){
            if(Nd!=nullptr)return true;
            else return false;
        } 



        /*
            ある地点を回転させる
        */
        void rotate(){

            SplayNode *Parent , *GrandParent , *Child;
            Parent = this->parent;
            GrandParent = Parent->parent;

            if(isExist(Parent) == false){
                return;
            }



            //元の親に対する位置で場合分け
            if(Parent->left == this){
                Child = this->right;//Childはnullptrかもしれない
                this->right = Parent;
                Parent->left = Child;

            }else if(Parent->right == this){
                Child = this->left;
                this->left = Parent;
                Parent->right = Child;

            }

            if(isExist(GrandParent)){
                //GrandParentのどちらの辺なのかで場合分け
                if(Parent == GrandParent->left){
                    GrandParent->left = this;

                }else if(Parent == GrandParent->right){
                    GrandParent->right = this;
                    
                }
            }

            //GrandParentがnullptrの場合でも代入OK
            this->parent = GrandParent;


            //親と位置を入れ替えるので
            Parent->parent = this;



            //Childは移動するので。
            if(isExist(Child))Child->parent = Parent;


            /*
                Nodeの持つ情報をupdateしないといけないが、順番に注意！！
                ChildはChild以下の部分木が変化してないので何もしなくてOK
                GrandParentは、部分木の中の順番が変わったけど、集合としては変わってないので何もしなくてOK
                Parentと自分自身(this)は順番が変わって、部分木の内容も変わったので、
                下から　Parent　⇨  this の順番でupdateする
            */
            Parent->update();
            this->update();

            

            return;

        }







        /*
            自分の親から見た自分の位置
            0 -> 親がそもそもいない or 例外の場合
            1 -> 親から見て左の子の場合
            2 -> 親から見て右の子の場合 
        */
        int state(){
            if(isExist(this->parent)== false){
                return 0;
            }else{
                if(this->parent->left == this){
                    return 1;
                }else if(this->parent->right == this){
                    return 2;
                }else {
                    return 0;
                }
            }
        }







        /*
            あるNodeを回転を駆使し一番上まで持っていく
            この時、回転する順番に注意
        */
        void splay(){



            while(isExist(this->parent)){
                if(isExist(this->parent->parent)==false){
                    //(自分のGrandParentがいない場合、rotateは一回のみ)
                    this->rotate();
                    return;


                //それ以外の場合、(自分、親、親の親)の位置関係が大事
                }else if(this->state() == this->parent->state()){
                    //GrandParentからの道が(右、右)or (左、左)の場合
                    //GrandParentを一つ下に下ろして、自分を上げる
                    this->parent->rotate();
                    this->rotate();

                }else{
                    //それ以外の場合、単純に自分を2回上に上げれば良い
                    this->rotate();
                    this->rotate();
                }
            }



            return;
        }   






        /*
            サイズなど、Nodeの持っている情報をupdateする(順番大事)
        */
        void update(){
            if(isExist(this) == false)return;
            this->SubTreeSize = 1;
            this->Min = this->Value;
            this->Max = this->Value;
            this->Sum = this->Value;


            if(isExist(this->left)){
                this->SubTreeSize += this->left->SubTreeSize;
                if(this->left->Min < this->Min)this->Min = this->left->Min;
                if(this->left->Max > this->Max)this->Max = this->left->Max;
                this->Sum += this->left->Sum;
            }

            if(isExist(this->right)){
                this->SubTreeSize += this->right->SubTreeSize;
                if(this->right->Min < this->Min)this->Min = this->right->Min;
                if(this->right->Max > this->Max)this->Max = this->right->Max;
                this->Sum += this->right->Sum;

            }

            return;
        }

    };



    /*
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
        ------------------------------------------------------------------------------------------------------------------------------------------------------------
            ここからやっとSplayTreeに載せる関数たちの出番
            rootを根とする部分木において、
              split(ind,root) , merge(l_root, r_root) , delete_sub(ind,root) , insert_sub()　など
            これらは主にclass内で使われる。
            classの外で使う関数として、
                Delete , insert, RangeSumQuery , shiftなどが想定される
        ------------------------------------------------------------------------------------------------------------------------------------------------------------   
        ------------------------------------------------------------------------------------------------------------------------------------------------------------

    */



    //これは、Nodeを管理する配列のサイズで、木のサイズではない(変更しないので、あらかじめ大きめにとっておく)
    int Size = 0;
    //この木のroot,splitした後はmergeして戻す！！rootが迷子にならないように！！
    SplayNode *Root = nullptr;




    MyMultiSet(){

    }

    MyMultiSet(int size_){
  
    }

    bool isExist(SplayNode *Nd){
        if(Nd==nullptr){
            return false;
        }else{
            return true;
        }
    }




    /*
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ここからは、クラス内で動かす関数たちです。俗にいうブラックボックスです。
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    */


    private:







    /*
        rootを根とする部分木において、
        indexを左からの0-indexとすると、

        求めたいindexになるまで降りていく

    */
    SplayNode *getNode(int index , SplayNode *root){
        
        if(isExist(root)==false)return root;
        

        SplayNode *now = root;


        while(1){

            int left_size = 0;
            if(isExist(now->left)){
                left_size = now->left->SubTreeSize;
            } 

            if(index < left_size){
                now = now->left;
            }else if(index == left_size){
                now->splay();
                break;
            }else if(index > left_size){
                now = now->right;
                index = index - left_size-1;
            }

        }
    

        return now;
    }













    /*
        それぞれ、leftrootとrightrootが根であるような部分木をくっつける

        splitした後、これをしてまたsplitしたものをくっつける
        splitしたまま放置すると分割された木のrootが行方不明になりそう
    */
    SplayNode *merge(SplayNode *leftRoot , SplayNode *rightRoot){

       
        if(isExist(leftRoot) == false)return rightRoot;//右のみあり
        if(isExist(rightRoot) == false )return leftRoot;//左のみあり


        leftRoot = getNode(leftRoot->SubTreeSize-1 , leftRoot);
        leftRoot->right = rightRoot;
        rightRoot->parent = leftRoot;
        leftRoot->update();
        
        return leftRoot;
    }









    /*
         rootを根とする部分木において、
        左からleftnum番目の頂点で左右にsplit。
        splitした後はmergeしないと,splitした木の頂点が行方不明になりそう
    */
    std::pair<SplayNode*,SplayNode*> split(int leftnum, SplayNode *root){

        if(leftnum<=0)return std::make_pair(nullptr , root);

        if(leftnum >= root->SubTreeSize)return std::make_pair(root, nullptr);



        root = getNode(leftnum , root);
        
        SplayNode *leftRoot , *rightRoot;

        leftRoot = root->left; 
        
        rightRoot = root; 

        
        if(isExist(rightRoot))rightRoot->left = nullptr;
        
        if(isExist(leftRoot))leftRoot->parent = nullptr; 
        
        rightRoot->update();


        return std::make_pair(leftRoot,rightRoot);

    }





    /*
         rootを根とする部分木において、
        indexの場所を切り離して、NODEを追加して元に戻す(merge)
    */
    SplayNode  *insert_sub( SplayNode *NODE , SplayNode *root){
        if(isExist(root) == false){
            root=NODE;
            Size=1;
            return root;
        }

        SplayNode *now = root;
        while(true){
            SplayNode *next = nullptr;
            if(now->Value>NODE->Value){
                if(isExist(now->left) == false){
                    now->left = NODE;
                    NODE->parent = now;
                    break;
                }else{
                    now = now->left;
                }
            }else{
                if(isExist(now->right) == false){
                    now->right = NODE;
                    NODE->parent = now;
                    break;
                }else{
                    now = now->right;
                }
            }

        }

        Size++;
        now->splay();

        return now;
    }








    /*  
        rootを根とする部分木において、
        左からindexの場所を削除して、両端をくっつける
        firstは消したやつ以外をmergeした時のroot
        secondは消したSplayNode
    */
    std::pair<SplayNode*,SplayNode*> Delete_sub(int index , SplayNode *root){
        
        if(isExist(root) == false){
            
            return std::make_pair(root,root);
        }
        if(index<0 || index >= Size){

            return std::make_pair(root,root);
        }
        
        if(Size == 1){

            Size = 0;
            root = nullptr;
            return std::make_pair(nullptr,nullptr);
        }

        root = getNode(index,root);

        SplayNode *leftRoot = root->left;
        SplayNode *rightRoot = root->right;

        if(isExist(leftRoot))leftRoot->parent = nullptr;
        if(isExist(rightRoot))rightRoot->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;

        Size--;
        
        root->update();
        
        return std::make_pair(merge(leftRoot,rightRoot) , root );
    }







    /*
        NODEと同じvalueをもつ要素をpop
    */
    std::pair<SplayNode*,SplayNode*> erase_sub(SplayNode *NODE , SplayNode *root){

        if(isExist(root)==false){
            return std::make_pair(root,root);
            
        }
        SplayNode *now = root;
        
        while(true){
            if(isExist(now)==false){
                //そもそもNODE.valueと同じvalueを持つ頂点がなかった時
                //何もせず終了
                return std::make_pair(root,root);
            }

            if(now->Value == NODE->Value){
                break;
            }else if(now->Value > NODE->Value){
                now = now->left;
            }else{
                now = now->right;
            }
        }

        root = now;
        root->splay();
        

        SplayNode *leftRoot = root->left;
        SplayNode *rightRoot = root->right;

        if(isExist(leftRoot))leftRoot->parent = nullptr;
        if(isExist(rightRoot))rightRoot->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;


        Size--;
        return std::make_pair(merge(leftRoot,rightRoot) , root );


    }







 







    /*
        rootを根とする部分木の[l,r)の区間取得クエリ
    */
    std::pair<SplayNode*,T> RangeQuery_sub(int l , int r , SplayNode *root){

        SplayNode *leftRoot , *centerRoot , *rightRoot; 
        r--;//半開区間なので

        std::pair<SplayNode*,SplayNode*>  tmp = split(r+1,root);
        rightRoot = tmp.second;
        
        tmp = split(l,tmp.first);
        leftRoot = tmp.first;
        centerRoot = tmp.second;

        T ans = centerRoot->Sum;

        return std::make_pair(merge(merge(leftRoot,centerRoot),rightRoot),ans);
    }






    /*
        rootが根であるような部分木の頂点のうち、val未満の頂点の個数を返す
    */
    std::pair<SplayNode*,int> lower_bound_sub(T val , SplayNode *root){
        if(isExist(root) == false)return std::make_pair(root,0);
        SplayNode *now = root;


        int res = root->SubTreeSize;
        if(isExist(now->right))res -= now->right->SubTreeSize;

        while(true){
            if(now->Value >=val){
                if(isExist(now->left)){
                    now = now->left;
                    res-=1;
                    if(isExist(now->right))res-=now->right->SubTreeSize;
                }
                else {
                    res--;
                    break;
                }
            }else{
                if(isExist(now->right)){
                    now = now->right;
                    res+=1;
                    if(isExist(now->left))res+=now->left->SubTreeSize;
                }
                else {
                    

                    break;
                }
            }
         
            
        }



        now->splay();
     

        return std::make_pair(now , res);


       
    }









    /*
        rootが根であるような部分木の頂点のうち、val以下の頂点の個数を返す
    */
    std::pair<SplayNode*,int> upper_bound_sub(T val , SplayNode *root){
        if(isExist(root) == false)return std::make_pair(root,0);
        SplayNode *now = root;


        int res = root->SubTreeSize;
        if(isExist(now->right))res -= now->right->SubTreeSize;

        while(true){

            if(now->Value > val){
                if(isExist(now->left)){
                    now = now->left;
                    res-=1;
                    if(isExist(now->right))res-=now->right->SubTreeSize;
                }
                else {
                    res--;
                    break;
                }
            }else{
                if(isExist(now->right)){
                    now = now->right;
                    res+=1;
                    if(isExist(now->left))res+=now->left->SubTreeSize;
                }
                else {
                    break;
                }
            }

  
         
            
        }

        now->splay();
     

        return std::make_pair(now , res);


       
    }








    /*
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ここからは、クラスの外で動かす関数たちです。
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    */



     public:



    /*
        木全体のindex番目のNode(値渡し)を取得
    */
    SplayNode get(int index){
        if(index<0 || index>=Size){
            std::cerr<< "index exceeds Size" << std::endl;
            return SplayNode(INF);
        }

        Root = getNode(index,Root);
        Root->update();

        return *(Root);

    }




    void insert( T val ){
        Root = insert_sub(new SplayNode(val) ,Root);
        Root->update();
        return;
    }



    /*
        index番目のNodeを消去
    */
    void Delete(int index){
        std::pair<SplayNode*,SplayNode*> tmp = Delete_sub(index,Root);
        
        Root = tmp.first;
        if(isExist(Root) == false )return;
        Root->update();

        return;
    }


    /*
        valを持つ頂点を一つpop
    */
    void erase(T val){
        Root = erase_sub(new SplayNode(val) , Root).first;
        Root->update();
        return;
    }



    /*
        小さい方からl番目以上、r番目未満の要素の和
    */
    T RangeSumQuery(int l , int r){
        l = max(0,l);
        r = min(Size,r);
        if(l>=r)return 0;

        std::pair<SplayNode*,T> tmp = RangeQuery_sub(l,r,Root);

        Root = tmp.first;
        Root->update();

        return tmp.second;
    }




    /*
        rootが根であるような部分木の頂点のうち、val未満の頂点の個数を返す
    */
    int lower_bound(T val){
        std::pair<SplayNode*,int> tmp = lower_bound_sub(val,Root);
        Root = tmp.first;
        Root->update();

        return tmp.second;
    }



    /*
        rootが根であるような部分木の頂点のうち、val以下の頂点の個数を返す
    */
    int upper_bound(T val){
        std::pair<SplayNode*,int> tmp = upper_bound_sub(val,Root);
        Root = tmp.first;
        Root->update();

        return tmp.second;

    }


    /*
        一列に表示
    */
    void Debug(){
        std::cerr<<"DEBUG:" << std::endl;
        for( int i = 0 ; i < Size ; i++){
            std::cerr<< get(i).Value << " ";
        }
        std::cerr<< std::endl;
    }


};







int main(){
    int q;cin >>q;

    SplayTree<long long> St;
    MyMultiSet<long long>Ms;
    
    for(int i = 0 ; i < q ; i++){
        int t,x,y;cin >> t;
        if(t==1){//push_backクエリ
            cin >> x;
            St.push_back(x);
        }else if(t==2){//sortクエリ
            while(St.Size>0){
                Ms.insert(St.get(0).Value);
                St.Delete(0);
            }
        }else{//mergeクエリ
            cin >> x >> y;
            x--;y--;
            long long res;
            if(Ms.Size<=x){
                res = St.RangeSumQuery(x-Ms.Size , y-Ms.Size);
            }else if(Ms.Size <= y){
                res = Ms.RangeSumQuery(x,Ms.Size) + St.RangeSumQuery(0,y-Ms.Size);
            }else{
                res = Ms.RangeSumQuery(x,y);
            }
            cout <<res << endl;
        }

        
    }

    return 0;
}





