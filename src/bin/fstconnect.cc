// See www.openfst.org for extensive documentation on this weighted
// finite-state transducer library.
//
// Removes useless (inaccessible or non-coaccessible) states and arcs from an
// FST.

#include <memory>
#include <string>

#include <fst/script/connect.h>

int main(int argc, char **argv) {
  namespace s = fst::script;
  using fst::script::FstClass;
  using fst::script::MutableFstClass;

  string usage = "Removes useless states and arcs from an FST.\n\n  Usage: ";
  usage += argv[0];
  usage += " [in.fst [out.fst]]\n";

  std::set_new_handler(FailedNewHandler);
  SET_FLAGS(usage.c_str(), &argc, &argv, true);
  if (argc > 3) {
    ShowUsage();
    return 1;
  }

  string in_name = (argc > 1 && strcmp(argv[1], "-") != 0) ? argv[1] : "";
  string out_name = argc > 2 ? argv[2] : "";

  std::unique_ptr<MutableFstClass> fst(MutableFstClass::Read(in_name, true));
  if (!fst) return 1;

  s::Connect(fst.get());

  fst->Write(out_name);

  return 0;
}
