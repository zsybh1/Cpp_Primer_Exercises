#pragma once
#include "..\QueryBase.h"
#include "..\TextQuery.h"
#include "..\QueryResult.h"
#include "..\Query.h"
#include <memory>
#include <algorithm>

class AndQuery: public QueryBase{
private:
    Query mFirst;
    Query mSecond;
public:
    AndQuery(const Query& firstQuery, const Query& secondQuery) : mFirst(firstQuery), mSecond(secondQuery){}
    QueryResult eval(const TextQuery& textQuery) const override ;

    friend Query operator&(const Query& firstQuery, const Query& secondQuery);
};

inline Query operator&(const Query& firstQuery, const Query& secondQuery){
    return Query(std::make_shared<AndQuery>(AndQuery(firstQuery, secondQuery)));
}

inline QueryResult AndQuery::eval(const TextQuery& textQuery) const {
    auto firstRes = mFirst.eval(textQuery);
    auto secondRes = mSecond.eval(textQuery);
    QueryResult queryResult;
    std::set_intersection(firstRes.begin(), firstRes.end(),
                secondRes.begin(), secondRes.end(),
                std::inserter(queryResult.getContainer(), queryResult.begin()));
    return queryResult;
}