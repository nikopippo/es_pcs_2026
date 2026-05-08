#include <iostream>
#include <vector>
#include <set>
#include <string>

#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"


/* Test completo con interi */
bool testIntegers() {

    bool wrong = false;

    unidirected_graph<int> g;

    /* add_edge */
    g.add_edge(unidirected_edge<int>(1,2));
    g.add_edge(unidirected_edge<int>(2,3));
    g.add_edge(unidirected_edge<int>(3,1));

    /* all_nodes */
    std::vector<int> nodes = g.all_nodes();

    if (nodes.size() != 3) {
        wrong = true;
    }

    /* all_edges */
    std::set<unidirected_edge<int>> edges = g.all_edges();

    if (edges.size() != 3) {
        wrong = true;
    }

    /* neighours */
    std::set<int> nbs = g.neighours(1);

    if (!nbs.contains(2) || !nbs.contains(3)) {
        wrong = true;
    }

    /* edge_number */
    int pos = g.edge_number(unidirected_edge<int>(1,2));

    if (pos < 0) {
        wrong = true;
    }

    /* edge_at */
    unidirected_edge<int> e = g.edge_at(0);

    if (!(e == unidirected_edge<int>(1,2) || e == unidirected_edge<int>(1,3) || e == unidirected_edge<int>(2,3))) {
        wrong = true;
    }

    /* operator- */
    unidirected_graph<int> g2;

    g2.add_edge(unidirected_edge<int>(1,2));

    unidirected_graph<int> diff = g - g2;

    if (diff.all_edges().size() != 2) {
        wrong = true;
    }

    /* operator< e == di edge */
    unidirected_edge<int> a(5,1);
    unidirected_edge<int> b(1,5);

    if (!(a == b)) {
        wrong = true;
    }

    if (!(a.from() == 1 && a.to() == 5)) {
        wrong = true;
    }

    return !wrong;
}


/* Test completo con stringhe */
bool testStrings() {

    bool wrong = false;

    unidirected_graph<std::string> g;

    /* add_edge */
    g.add_edge(unidirected_edge<std::string>("Gianni", "Filippo"));
    g.add_edge(unidirected_edge<std::string>("Claudia", "Gianni"));
    g.add_edge(unidirected_edge<std::string>("Napoli", "Filippo"));

    /* all_nodes */
    std::vector<std::string> nodes = g.all_nodes();

    if (nodes.size() != 4) {
        wrong = true;
    }

    /* all_edges */
    std::set<unidirected_edge<std::string>> edges = g.all_edges();

    if (edges.size() != 3) {
        wrong = true;
    }

    /* neighours */
    std::set<std::string> nbs = g.neighours("Gianni");

    if (!nbs.contains("Filippo") || !nbs.contains("Claudia")) {
        wrong = true;
    }

    /* edge_number */
    int pos = g.edge_number(
        unidirected_edge<std::string>("Gianni","Filippo")
    );

    if (pos < 0) {
        wrong = true;
    }

    /* edge_at */
    unidirected_edge<std::string> e = g.edge_at(0);

    if (e.from().empty() || e.to().empty()) {
        wrong = true;
    }

    /* operator- */
    unidirected_graph<std::string> g2;

    g2.add_edge(
        unidirected_edge<std::string>("Gianni","Filippo")
    );

    unidirected_graph<std::string> diff = g - g2;

    if (diff.all_edges().size() != 2) {
        wrong = true;
    }

    /* operator== e ordinamento edge */
    unidirected_edge<std::string> a("zorro","bidet");
    unidirected_edge<std::string> b("bidet","zorro");

    if (!(a == b)) {
        wrong = true;
    }

    if (!(a.from() == "bidet" &&
          a.to() == "zorro")) {
        wrong = true;
    }

    return !wrong;
}


int main(void)
{
    if (!testIntegers()) return EXIT_FAILURE;
    if (!testStrings()) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}