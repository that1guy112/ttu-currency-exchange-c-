//
// Created by manum on 23-Feb-26.
//

#ifndef TTU_CURRENCY_EXCHANGE_C__CONVERT_CURRENCY_H
#define TTU_CURRENCY_EXCHANGE_C__CONVERT_CURRENCY_H

class convert_currency {
    public:
    double convert_currency_func(const std::string& fromCurrency,
                                 const std::string& toCurrency,
                                 double amount);
};

#endif //TTU_CURRENCY_EXCHANGE_C__CONVERT_CURRENCY_H