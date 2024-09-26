#include <catch2/catch_test_macros.hpp>
// #include <catch2/generators/catch_generators_all.hpp>
#include "funciones.cpp"

TEST_CASE("Calcula media deberia funcionar", "[test_funciones]") {
    double resultado = calcula_media({10, 10, 10});
    CHECK(resultado == 10);

    CHECK(calcula_media({5, 3, 4}) == 4);
    CHECK(calcula_media({6, 8, 4}) == 6);
    CHECK(calcula_media({2, 8, 5}) == 5);
}

TEST_CASE("Al cubo deberia funcionar", "[test_funciones]") {
    CHECK(al_cubo(2) == 8);
    CHECK(al_cubo(-2) == -8);
    CHECK(al_cubo(2) != 4);
    CHECK(al_cubo(-3) != 27);
}

TEST_CASE("Es par deberia funcionar", "[test_funciones]") {
    CHECK_FALSE(es_par(5));
    CHECK(es_par(2));
    CHECK(es_par(8));
    CHECK_FALSE(es_par(7));
    CHECK_FALSE(es_par(13));
    CHECK(es_par(72));
}

TEST_CASE("Decir hola deberia funcionar", "[test_funciones]") {
    CHECK(decir_hola("Pedro") == "Hola Pedro");
    CHECK(decir_hola("Juan") == "Hola Juan");
    CHECK(decir_hola("Carlos") != "Hola Carlo");
    CHECK(decir_hola("Ruben") != "Hola Rube");
}

