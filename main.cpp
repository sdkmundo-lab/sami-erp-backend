#include "httplib.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
    httplib::Server svr;

    // نقطة الاتصال (Endpoint) اللي الموقع هيكلمها
    svr.Get("/calculate", [](const httplib::Request& req, httplib::Response& res) {
        double amount = 0;
        if (req.has_param("amount")) {
            amount = std::stod(req.get_param_value("amount"));
        }

        // منطق الحسابات حسب متطلبات مشروع سامي (VAT 5% & Retention 10%)
        double vat = amount * 0.05;
        double retention = amount * 0.10;
        double net = (amount + vat) - retention;

        // تجهيز الرد بصيغة JSON عشان الـ HTML يفهمه
        std::stringstream ss;
        ss << "{"
           << "\"vat\":" << std::fixed << std::setprecision(2) << vat << ","
           << "\"retention\":" << retention << ","
           << "\"net\":" << net
           << "}";

        // السماح للموقع بالوصول للمحرك من سيرفر مختلف (CORS)
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(ss.str(), "application/json");
    });

    std::cout << "Sami ERP Engine is starting on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}