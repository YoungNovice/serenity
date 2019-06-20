#include <LibCore/CFile.h>
#include <LibHTML/Dump.h>
#include <LibHTML/Frame.h>
#include <LibHTML/Parser/Parser.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    CFile f(argc == 1 ? "/home/anon/small.html" : argv[1]);
    if (!f.open(CIODevice::ReadOnly)) {
        fprintf(stderr, "Error: %s\n", f.error_string());
        return 1;
    }
    String html = String::copy(f.read_all());
    auto doc = parse(html);
    dump_tree(doc);

    doc->build_layout_tree();
    ASSERT(doc->layout_node());

    printf("\033[33;1mLayout tree before layout:\033[0m\n");
    dump_tree(*doc->layout_node());

    auto frame = make<Frame>();
    frame->set_document(doc);
    frame->layout();

    printf("\033[33;1mLayout tree after layout:\033[0m\n");
    dump_tree(*doc->layout_node());
    return 0;
}
