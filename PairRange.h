#pragma once

#include<utility>

template<typename FirstItr_t, typename SecondItr_t>
class PairIterator{
    private:
        FirstItr_t FirstItr;
        SecondItr_t SecondItr;
    public:
        PairIterator(const FirstItr_t &f_itr, const SecondItr_t &s_itr)
            : FirstItr(f_itr), SecondItr(s_itr){
        }
        std::pair<decltype(*FirstItr)&, decltype(*SecondItr)&> operator*(){
            return std::pair<decltype(*FirstItr)&, decltype(*SecondItr)&>(*FirstItr,*SecondItr);
        }
        PairIterator& operator++(){
            ++FirstItr;
            ++SecondItr;

            return (*this);
        }
        bool operator!=(const PairIterator& rhs){   //安全重視で短いほうに合わせる
            return (FirstItr!=rhs.FirstItr) && (SecondItr!=rhs.SecondItr);
        }
};
template<class FirstCtnr_t,class SecondCtnr_t>
class PairContainer{
    private:
        FirstCtnr_t &FirstCtnr;
        SecondCtnr_t &SecondCtnr;
        PairContainer();
    public:
        PairContainer(FirstCtnr_t &f, SecondCtnr_t &s)
            : FirstCtnr(f), SecondCtnr(s){
        }
        using PairItr_t =  PairIterator<decltype(FirstCtnr.begin()), decltype(SecondCtnr.begin())>;
        PairItr_t begin(){
            return PairItr_t(FirstCtnr.begin(), SecondCtnr.begin());
        }
        PairItr_t end(){
            return PairItr_t(FirstCtnr.end(), SecondCtnr.end());
        }
};

template<typename FirstCtnr_t, typename SecondCtnr_t>
PairContainer<FirstCtnr_t,SecondCtnr_t> PairRange(FirstCtnr_t &first, SecondCtnr_t &second){
    return PairContainer<FirstCtnr_t,SecondCtnr_t>(first,second);
}