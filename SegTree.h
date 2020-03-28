#pragma once

#include<algorithm>

template<unsigned depth, typename T, typename Compare_T=std::greater<T>>
class SegTree{
    private:
        T Max;
        SegTree<depth-1, T, Compare_T> Children[2];
    public:
        SegTree(T DefVal): Max(DefVal), Children{T(DefVal), T(DefVal)} {
        }
        T GetMax(){
            return Max;
        }
        T GetRangeMax(unsigned RangeMin, unsigned RangeMax){
            if(RangeMin == 0 && RangeMax == (((1u)<<depth)-1) )
                return Max;
            else if(RangeMax < ((1u)<<(depth-1)) )
                return Children[0].GetRangeMax(RangeMin, RangeMax);
            else if(RangeMin >= ((1u)<<(depth-1)))
                return Children[1].GetRangeMax(RangeMin - ((1u)<<(depth-1)), RangeMax - ((1u)<<(depth-1)) );
            else{
                T tmp1 = Children[0].GetRangeMax(RangeMin, ((1u)<<depth)-1 );
                T tmp2 = Children[1].GetRangeMax(0, RangeMax - ((1u)<<(depth-1)) );

                return (Compare_T()(tmp1,tmp2))? tmp1 : tmp2;
            }
        }
        T GetVal(unsigned n){
            return Children[n / ((1u)<<(depth-1)) ].GetVal(n % ((1u)<<(depth-1)) );
        }
        void SetVal(unsigned n, T Val){
            if(Compare_T()(Val, Max))
                Max = Val;
            Children[n / ((1u)<<(depth-1)) ].SetVal(n % ((1u)<<(depth-1)), Val);
            return;
        }
};

template<typename T, typename Compare_T>
class SegTree<0, T, Compare_T>{
    private:
        T Max;
    public:
        SegTree(T DefVal): Max(DefVal){
        }
        T GetMax(){
            return Max;
        }
         T GetRangeMax(unsigned RangeMin, unsigned RangeMax){
             return Max;
         }
        T GetVal(unsigned n){
            return Max;
        }
        void SetVal(unsigned n, T Val){
            Max = Val;
        }
};




