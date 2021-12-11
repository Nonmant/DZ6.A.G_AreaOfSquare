#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "6\n"
                "7\n"
                "38"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "2"
    );
}

TEST_CASE("0 width", ""){
    std::stringstream input(
            "5 3 11"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "0"
    );
}

TEST_CASE("full width", ""){
    std::stringstream input(
            "4 4 16"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "2"
    );
}

TEST_CASE("more than full width", ""){
    std::stringstream input(
            "4 4 100"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "2"
    );
}

TEST_CASE("one side collapse", ""){
    std::stringstream input(
            "5 3 100"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "1"
    );
}

TEST_CASE("ranges", ""){
    std::stringstream input(
            "2000000000 2000000000 3999999999999999999"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "999999999"
    );
}
