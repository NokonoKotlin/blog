//include
//------------------------------------------
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<stack>
#include<string>
#include<complex>
#include<algorithm>
using namespace std;
const long long INF = 1e18;
const double PI = 3.141592653589793;











/*
    k demensional Tree
    k次元座標上に、あらかじめいくつかの点が与えられる。このライブラリではk = 2。
    クエリ１ ... 矩形:[sx,tx]×[sy,ty]の内部(周上を含む)に存在する点を列挙できる。
    クエリ２ ... 点(x,y)から、与えられた点のうち最も近いものへの距離を計算できる。
    


    addPointで点を与える(頂点を追加する)。ただし、追加した後はbuildをしないといけないので、高速ではない。
    buildで木を構築する。

    Rootは全体の根で、大事なので書き換えたりしてわからなくならないように気を付けてください。
    
    find_included_points : クエリ１
    find_nearest_dist : クエリ２

*/
template<class T>
class kdTree{


    public:
    /*
        ----------------------------------------------------------------------------------------------------------------------------------------
        ----------------------------------------------------------------------------------------------------------------------------------------
                            クラス内で使う構造体。クラス外からもアクセス可能
        ----------------------------------------------------------------------------------------------------------------------------------------    
        ----------------------------------------------------------------------------------------------------------------------------------------
    */

    struct Point{

        T x , y;//座標

        /*
            identifer : この点がどの点かを判断する
            kDtreeでは点をソートしたりするので、どの点がどこに行ったのかごちゃごちゃになりやすい。
            なので、点にidを与えることで、どこにどの点があるのかを判断する。
        */  
        int id;

        Point(T x_ , T y_ , int id_){
            x = x_;
            y = y_;
            id = id_;
        }

        Point(){}

    };


    struct Node{
        public:
        Node *left , *right ;

        Point val;

        Node(Node *left_ , Node *right_ , Point val_){
            left = left_;
            right = right_;
            val = val_;
        }

        Node(){
            left = nullptr;
            right = nullptr;
        }

    };


    private:
    /*
        ----------------------------------------------------------------------------------------------------------------------------------------
        ----------------------------------------------------------------------------------------------------------------------------------------
                            クラス内で行う処理。目には見えないブラックボックスってやつ
        ----------------------------------------------------------------------------------------------------------------------------------------    
        ----------------------------------------------------------------------------------------------------------------------------------------
    */
    int demension = 2;//次元。高くなると遅くなるよ



    //x座標で大小比較
    static bool compX(Point a , Point b){
        return a.x < b.x;
    }



    //y座標で大小比較
    static bool compY(Point a , Point b){
        return a.y < b.y;
    }





    /*
        P_listを元に木を作る。
        [lef,rig) の区間に対応する部分木の根を作る。
    */
    Node *build_sub(int lef = 0, int rig = 1e9 , int depth = 0){
        if(rig >= P_list.size())rig = P_list.size();
        if(lef< 0)lef = 0;
        if(lef>=rig){
            return nullptr;
        }

        int mid = (lef+rig)/2;

        //depth(階層)によってソートする座標軸を変える。二次元なので２通り
        if(depth%2==1){
            sort(P_list.begin()+ lef , P_list.begin() + rig , compX);
        }else{
            sort(P_list.begin()+ lef , P_list.begin() + rig , compY);
            
        }
        
        return new Node(build_sub(lef,mid ,depth+1) , build_sub(mid+1 ,rig , depth+1) , P_list[mid]);

    }


    /*
        点(x,y)から、一番近い点の距離(の二乗)を求める
    */
    T find_nearest_dist_sub(T x, T y,  int depth, Node *nd , T r = -1 ) {
        if(nd == nullptr) return r;

        Point p = nd->val;
        
        T d = (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);

        if(r == -1 || d < r) r = d;

        /*
            階層によって、座標軸が違うので場合分け
        */
        if(depth % 2) {
            /*      
                なんかとりあえず二分探索みたいなことをする
            */
            if(nd->left != nullptr && x - r <= p.x) {
                r = find_nearest_dist_sub(x, y,  depth+1 , nd->left , r);
            }
            if(nd->right != nullptr && p.x <= x + r) {
                r = find_nearest_dist_sub(x, y,  depth+1 , nd->right , r);
            }
        } else {
            if(nd->left != nullptr && y - r <= p.y) {
                r = find_nearest_dist_sub(x, y,  depth+1 , nd->left , r);
            }
            if(nd->right != nullptr && p.y <= y + r) {
                r = find_nearest_dist_sub(x, y,  depth+1 , nd->right , r);  
            }
        }

        return r;
    }



    /*
        矩形:[(sx,sy) , (tx,ty)]に含まれる点のidを,found_Points_IDに入れていく
    */
    void find_included_points_sub(Node *nd, T sx, T tx, T sy, T ty, int depth) {
        Point p = nd->val;

        if(sx>tx)swap(sx,tx);
        if(sy>ty)swap(sy,ty);

        if(sx <= p.x && p.x <= tx && sy <= p.y && p.y <= ty) {
            found_Points.push_back(p);
        }

        if(depth % 2) {
            if(nd->left != nullptr && sx <= p.x) {
                find_included_points_sub(nd->left, sx, tx, sy, ty, depth+1);
            }
            if(nd->right != nullptr && p.x <= tx) {
                find_included_points_sub(nd->right, sx, tx, sy, ty, depth+1);
            }
        } else {
            if(nd->left != nullptr && sy <= p.y) {
                find_included_points_sub(nd->left, sx, tx, sy, ty, depth+1);
            }
            if(nd->right != nullptr && p.y <= ty) {
                find_included_points_sub(nd->right,  sx, tx, sy, ty, depth+1);
            }
        }
    }

    





    public:
    /*
        ----------------------------------------------------------------------------------------------------------------------------------------
        ----------------------------------------------------------------------------------------------------------------------------------------
                            クラス外で行う処理。
        ----------------------------------------------------------------------------------------------------------------------------------------    
        ----------------------------------------------------------------------------------------------------------------------------------------
    */

    //全体の根,記憶しておくこと。どっかになくしたらだめ
    Node *Root = nullptr;

    /*
        addPointでPointを追加していく。
        ただし、追加した後はbuildで木を構築しないといけないので、追加はO(n)
    */
    vector<Point> P_list;

    /*
        find_included_pointsで取得した点を入れる配列
    */
    vector<Point> found_Points;


    

    //コンストラクタ
    kdTree(){
        
    }



    /*
        Pointを追加。ただし、追加した後に木を構築しないといけないので、O(n)
        また、次元は適宜変えてください。
    */
    void addPoint(T x , T y){
        int id_ = P_list.size();
        P_list.push_back(Point(x,y,id_));
    }






    /*
        build_subを使い、Rootを求める
    */
    void build(){
        Root = nullptr;//前の情報が残っていたらなんか嫌だから
        Root = build_sub();
    }





    /*
        点(x,y)から、一番近い点の距離(の二乗)を求める
    */
    T find_nearest_dist(T x ,T y){
        return find_nearest_dist_sub(x,y,0,Root,-1);
    }






    /*
        矩形:[(sx,sy) , (tx,ty)]に含まれる点のidを,found_Points_IDに入れていく
        引数は(sx , tx , sy , ty)なので注意
    */
    void find_included_points(T sx , T tx ,T sy , T ty){
        vector<Point>(0).swap(found_Points);
        find_included_points_sub(Root , sx ,tx , sy , ty , 0);
    }





};











int main(){

    kdTree<long long> K;

    
    int n;
    cin >> n;

    for(int i = 0 ; i < n ;i++ ){
        long long x , y;
        cin >> x >> y;
        K.addPoint(x,y);
    }
    K.build();
    int q;cin >> q;
    
    while(q-->0){
        long long sx,sy,tx,ty;
        cin >> sx >> tx >> sy >> ty;
        K.find_included_points(sx,tx,sy,ty);
        priority_queue<int , vector<int> ,greater<int> >pq;
        for(kdTree<long long>::Point p : K.found_Points){
            pq.push(p.id);
        }
        while(pq.size()>0){
            printf("%d\n" , pq.top());
            pq.pop();
        }
        cout << endl;
    }



    return 0;
}