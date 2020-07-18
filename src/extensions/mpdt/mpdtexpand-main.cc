// See www.openfst.org for extensive documentation on this weighted
// finite-state transducer library.
//
// Expands a (bounded-stack) MPDT as an FST.

#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <fst/flags.h>
#include <fst/types.h>
#include <fst/log.h>
#include <fst/extensions/mpdt/mpdtscript.h>
#include <fst/extensions/mpdt/read_write_utils.h>
#include <fst/util.h>

DECLARE_string(mpdt_parentheses);
DECLARE_bool(connect);
DECLARE_bool(keep_parentheses);

int mpdtexpand_main(int argc, char **argv) {
  namespace s = fst::script;
  using fst::MPdtExpandOptions;
  using fst::ReadLabelTriples;
  using fst::script::FstClass;
  using fst::script::VectorFstClass;

  std::string usage = "Expand a (bounded-stack) MPDT as an FST.\n\n  Usage: ";
  usage += argv[0];
  usage += " in.pdt [out.fst]\n";

  std::set_new_handler(FailedNewHandler);
  SET_FLAGS(usage.c_str(), &argc, &argv, true);
  if (argc > 3) {
    ShowUsage();
    return 1;
  }

  const std::string in_name =
      (argc > 1 && (strcmp(argv[1], "-") != 0)) ? argv[1] : "";
  const std::string out_name =
      (argc > 2 && (strcmp(argv[2], "-") != 0)) ? argv[2] : "";

  std::unique_ptr<FstClass> ifst(FstClass::Read(in_name));
  if (!ifst) return 1;

  if (FLAGS_mpdt_parentheses.empty()) {
    LOG(ERROR) << argv[0] << ": No MPDT parenthesis label pairs provided";
    return 1;
  }

  std::vector<std::pair<int64, int64>> parens;
  std::vector<int64> assignments;
  if (!ReadLabelTriples(FLAGS_mpdt_parentheses, &parens, &assignments, false)) {
    return 1;
  }

  VectorFstClass ofst(ifst->ArcType());

  const MPdtExpandOptions opts(FLAGS_connect, FLAGS_keep_parentheses);

  s::MPdtExpand(*ifst, parens, assignments, &ofst, opts);

  return !ofst.Write(out_name);
}
