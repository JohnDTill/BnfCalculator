#include "numberliteralnode.h"

#include "rationalliteralnode.h"

AstNode* NumberLiteralNode::simplify() {
    bool is_negative = (val.at(0) == '-');
    std::string mag = is_negative ? val.substr(1,val.size()-1) : val;

    unsigned long long decimal = 0;
    for(unsigned long long i = 0; i < mag.size(); i++){
        if(mag[i]=='.'){
            decimal = i;
            break;
        }
    }

    std::string den = "1";
    std::string num = mag;
    if(decimal){
        num.erase(decimal,1);
        for(unsigned long long i = decimal+1; i < mag.size(); i++)
            den.push_back('0');
    }

    big_uint n(num);
    big_uint d(den);
    rational r(n, d, is_negative);

    return new RationalLiteralNode(r);
}
