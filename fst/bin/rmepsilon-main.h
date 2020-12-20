// rmepsilon-main.h
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: riley@google.com (Michael Riley)
//
// \file
// Removes epsilons from an FST. Includes helper function for
// fstrmepsilon.cc that templates the main on the arc type to support
// multiple and extensible arc types.

#ifndef FST_RMEPSILON_MAIN_H__
#define FST_RMEPSILON_MAIN_H__

#include "fst/bin/main.h"
#include "fst/lib/rmepsilon.h"
#include "fst/lib/vector-fst.h"

DECLARE_bool(connect);
DECLARE_bool(reverse);

namespace fst {

// Main function for fstrmepsilon templated on the arc type.
template <class Arc>
int RmEpsilonMain(int argc, char **argv, istream &strm,
             const FstReadOptions &opts) {
  Fst<Arc> *ifst = Fst<Arc>::Read(strm, opts);
  if (!ifst) return 1;

  MutableFst<Arc> *ofst = 0;

  if (FLAGS_reverse) {
    {
      VectorFst< ReverseArc<Arc> > rfst;
      Reverse(*ifst, &rfst);
      delete ifst;
      RmEpsilon(&rfst, FLAGS_connect);
      ofst = new VectorFst<Arc>;
      Reverse(rfst, ofst);
    }
    RmEpsilon(ofst, FLAGS_connect);
  } else {
    if (ifst->Properties(kMutable, false)) {
      ofst = down_cast<MutableFst<Arc> *>(ifst);
    } else {
      ofst = new VectorFst<Arc>(*ifst);
      delete ifst;
    }
    RmEpsilon(ofst, FLAGS_connect);
  }
  ofst->Write(argc > 2 ? argv[2] : "");

  return 0;
}

}  // namespace fst

#endif  // FST_RMEPSILON_MAIN_H__
