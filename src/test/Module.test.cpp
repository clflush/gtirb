//===- Module.test.cpp ------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2018 GrammaTech, Inc.
//
//  This code is licensed under the MIT license. See the LICENSE file in the
//  project root for license terms.
//
//  This project is sponsored by the Office of Naval Research, One Liberty
//  Center, 875 N. Randolph Street, Arlington, VA 22203 under contract #
//  N68335-17-C-0700.  The content of the information does not necessarily
//  reflect the position or policy of the Government and no official
//  endorsement should be inferred.
//
//===----------------------------------------------------------------------===//
#include <gtirb/AuxData.hpp>
#include <gtirb/CodeBlock.hpp>
#include <gtirb/Context.hpp>
#include <gtirb/DataBlock.hpp>
#include <gtirb/Module.hpp>
#include <gtirb/Section.hpp>
#include <gtirb/Symbol.hpp>
#include <gtirb/SymbolicExpression.hpp>
#include <proto/Module.pb.h>
#include <algorithm>
#include <gtest/gtest.h>
#include <iterator>
#include <tuple>
#include <utility>

using namespace gtirb;

TEST(Unit_Module, compilationIteratorTypes) {
  static_assert(
      std::is_same_v<Module::code_block_iterator::reference, CodeBlock&>);
  static_assert(std::is_same_v<Module::const_code_block_iterator::reference,
                               const CodeBlock&>);
  static_assert(std::is_same_v<Module::code_block_subrange::iterator::reference,
                               CodeBlock&>);
  static_assert(
      std::is_same_v<Module::const_code_block_subrange::iterator::reference,
                     const CodeBlock&>);
  // Actually calling the constructor and assignment operator tends to produce
  // more informative error messages than std::is_constructible and
  // std::is_assignable.
  {
    Module::code_block_iterator it;
    Module::const_code_block_iterator cit(it);
    cit = it;
  }

  static_assert(
      std::is_same_v<Module::data_block_iterator::reference, DataBlock&>);
  static_assert(std::is_same_v<Module::const_data_block_iterator::reference,
                               const DataBlock&>);
  static_assert(std::is_same_v<Module::data_block_subrange::iterator::reference,
                               DataBlock&>);
  static_assert(
      std::is_same_v<Module::const_data_block_subrange::iterator::reference,
                     const DataBlock&>);
  {
    Module::data_block_iterator it;
    Module::const_data_block_iterator cit(it);
    cit = it;
  }

  static_assert(std::is_same_v<Module::section_iterator::reference, Section&>);
  static_assert(std::is_same_v<Module::const_section_iterator::reference,
                               const Section&>);
  static_assert(
      std::is_same_v<Module::section_name_iterator::reference, Section&>);
  static_assert(std::is_same_v<Module::const_section_name_iterator::reference,
                               const Section&>);
  static_assert(
      std::is_same_v<Module::section_subrange::iterator::reference, Section&>);
  static_assert(
      std::is_same_v<Module::const_section_subrange::iterator::reference,
                     const Section&>);

  {
    Module::section_iterator it;
    Module::const_section_iterator cit(it);
    cit = it;
  }

  {
    Module::section_name_iterator it;
    Module::const_section_name_iterator cit(it);
    cit = it;
  }

  static_assert(std::is_same_v<Module::symbolic_expression_iterator::reference,
                               SymbolicExpression&>);
  static_assert(
      std::is_same_v<Module::const_symbolic_expression_iterator::reference,
                     const SymbolicExpression&>);
  static_assert(
      std::is_same_v<Module::symbolic_expression_addr_iterator::reference,
                     SymbolicExpression&>);
  static_assert(
      std::is_same_v<Module::const_symbolic_expression_addr_iterator::reference,
                     const SymbolicExpression&>);

  static_assert(std::is_same_v<Module::symbol_iterator::reference, Symbol&>);
  static_assert(
      std::is_same_v<Module::const_symbol_iterator::reference, const Symbol&>);
  static_assert(
      std::is_same_v<Module::symbol_addr_iterator::reference, Symbol&>);
  static_assert(std::is_same_v<Module::const_symbol_addr_iterator::reference,
                               const Symbol&>);

  {
    Module::symbol_iterator it;
    Module::const_symbol_iterator cit(it);
    cit = it;
  }
}

static Context Ctx;

TEST(Unit_Module, ctor_0) { EXPECT_NE(Module::Create(Ctx, nullptr), nullptr); }

TEST(Unit_Module, setBinaryPath) {
  const std::string StrPath("/home/gt/irb/foo");
  auto* M = Module::Create(Ctx, nullptr);

  M->setBinaryPath(StrPath);

  auto Path = M->getBinaryPath();
  EXPECT_EQ(StrPath, Path);
}

TEST(Unit_Module, getFileFormatDefault) {
  auto* M = Module::Create(Ctx, nullptr);
  EXPECT_EQ(gtirb::FileFormat::Undefined, M->getFileFormat());
}

TEST(Unit_Module, auxDataRanges) {
  Module* Ml = Module::Create(Ctx, nullptr);
  Ml->addAuxData("foo", std::vector<int64_t>{1, 2, 3});
  Ml->addAuxData("bar", std::vector<char>{'a', 'b', 'c'});

  auto A = Ml->aux_data();
  EXPECT_EQ(std::distance(A.begin(), A.end()), 2);
  // AuxDatas are sorted by range, but this is an implementation detail
  EXPECT_EQ(A.begin()->first, "bar");
  EXPECT_EQ((++A.begin())->first, "foo");
}

TEST(Unit_Module, setFileFormat) {
  auto* M = Module::Create(Ctx, nullptr);

  M->setFileFormat(gtirb::FileFormat::COFF);
  EXPECT_EQ(gtirb::FileFormat::COFF, M->getFileFormat());

  M->setFileFormat(gtirb::FileFormat::MACHO);
  EXPECT_EQ(gtirb::FileFormat::MACHO, M->getFileFormat());

  M->setFileFormat(gtirb::FileFormat::Undefined);
  EXPECT_EQ(gtirb::FileFormat::Undefined, M->getFileFormat());
}

TEST(Unit_Module, getRebaseDeltaDefault) {
  auto* M = Module::Create(Ctx, nullptr);
  EXPECT_EQ(int64_t{0}, M->getRebaseDelta());
}

TEST(Unit_Module, setRebaseDelta) {
  auto* M = Module::Create(Ctx, nullptr);

  EXPECT_FALSE(M->isRelocated());

  M->setRebaseDelta(1);
  EXPECT_EQ(int64_t{1}, M->getRebaseDelta());
  EXPECT_TRUE(M->isRelocated());

  M->setRebaseDelta(-1);
  EXPECT_EQ(int64_t{-1}, M->getRebaseDelta());
  EXPECT_TRUE(M->isRelocated());

  M->setRebaseDelta(std::numeric_limits<int64_t>::max());
  EXPECT_EQ(std::numeric_limits<int64_t>::max(), M->getRebaseDelta());
  EXPECT_TRUE(M->isRelocated());

  M->setRebaseDelta(std::numeric_limits<int64_t>::min());
  EXPECT_EQ(std::numeric_limits<int64_t>::min(), M->getRebaseDelta());
  EXPECT_TRUE(M->isRelocated());

  M->setRebaseDelta(std::numeric_limits<int64_t>::lowest());
  EXPECT_EQ(std::numeric_limits<int64_t>::lowest(), M->getRebaseDelta());
  EXPECT_TRUE(M->isRelocated());
}

TEST(Unit_Module, getPreferredAddrDefault) {
  auto* M = Module::Create(Ctx, nullptr);
  EXPECT_EQ(Addr{}, M->getPreferredAddr());
}

TEST(Unit_Module, getISAID) {
  auto* M = Module::Create(Ctx, nullptr);

  EXPECT_EQ(gtirb::ISAID::Undefined, M->getISAID());

  M->setISAID(gtirb::ISAID::X64);
  EXPECT_EQ(gtirb::ISAID::X64, M->getISAID());
}

TEST(Unit_Module, setPreferredAddr) {
  auto* M = Module::Create(Ctx, nullptr);
  Addr Preferred{64};

  EXPECT_EQ(M->getPreferredAddr(), Addr(0));

  M->setPreferredAddr(Preferred);
  EXPECT_EQ(Preferred, M->getPreferredAddr());
}

TEST(Unit_Module, getSymbolSet) {
  auto* M = Module::Create(Ctx, nullptr);
  EXPECT_EQ(std::distance(M->symbols().begin(), M->symbols().end()), 0);
}

TEST(Unit_Module, getName) {
  auto* M = Module::Create(Ctx, nullptr);
  EXPECT_TRUE(M->getName().empty());
}

TEST(Unit_Module, sections) {
  auto* M = Module::Create(Ctx, nullptr);
  M->addSection(Ctx, "test");
  EXPECT_EQ(M->section_begin()->getName(), "test");
  EXPECT_EQ(std::distance(M->section_begin(), M->section_end()), 1);
  EXPECT_EQ(std::distance(M->section_by_name_begin(), M->section_by_name_end()),
            1);
}

TEST(Unit_Module, findSection) {
  auto* M = Module::Create(Ctx, nullptr);
  auto* S = M->addSection(Ctx, "test");
  S->addByteInterval(Ctx, Addr(1), 123);

  {
    auto F = M->findSection(Addr(1));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(F.begin()->getName(), "test");

    F = M->findSection(Addr(123));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);

    F = M->findSection(Addr(124));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);
  }

  {
    auto F = M->findSection("test");
    EXPECT_NE(F, M->section_by_name_end());
    EXPECT_EQ(F->getName(), "test");

    F = M->findSection("dummy");
    EXPECT_EQ(F, M->section_by_name_end());
  }
}

TEST(Unit_Module, blocks) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(1), 10);
  BI->addCodeBlock(Ctx, 0, 10);

  EXPECT_EQ(std::distance(M->code_blocks_begin(), M->code_blocks_end()), 1);
  EXPECT_EQ(M->code_blocks_begin()->getAddress(), std::optional<Addr>(Addr(1)));

  auto F = blocks(M->getCFG());
  EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
  EXPECT_EQ(F.begin()->getAddress(), Addr(1));
}

TEST(Unit_Module, cfgNodes) {
  auto* M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(1), 10);
  auto* B = BI->addCodeBlock(Ctx, 0, 10);
  auto* P = M->addProxyBlock(Ctx);

  EXPECT_EQ(std::distance(M->code_blocks_begin(), M->code_blocks_end()), 1);
  auto Nodes = nodes(M->getCFG());
  EXPECT_EQ(std::distance(Nodes.begin(), Nodes.end()), 2);
  auto It = Nodes.begin();
  EXPECT_TRUE(&*It == B || &*It == P);
  ++It;
  EXPECT_NE(&*Nodes.begin(), &*It);
  EXPECT_TRUE(&*It == B || &*It == P);
}

TEST(Unit_Module, findBlock) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(0), 30);
  auto* B1 = BI->addCodeBlock(Ctx, 1, 20);
  auto* B2 = BI->addCodeBlock(Ctx, 5, 10);

  {
    auto F = M->findCodeBlock(Addr(0));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);

    F = M->findCodeBlock(Addr(1));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), B1);

    F = M->findCodeBlock(Addr(5));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(&*F.begin(), B1);
    EXPECT_EQ(&*++F.begin(), B2);

    F = M->findCodeBlock(Addr(14));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(&*F.begin(), B1);
    EXPECT_EQ(&*++F.begin(), B2);

    F = M->findCodeBlock(Addr(15));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), B1);

    F = M->findCodeBlock(Addr(20));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), B1);

    F = M->findCodeBlock(Addr(21));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);
  }
}

TEST(Unit_Module, dataObjects) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(1), 123);
  BI->addDataBlock(Ctx, 0, 123);
  EXPECT_EQ(M->data_blocks_begin()->getAddress(), Addr(1));
}

TEST(Unit_Module, findData) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(0), 30);

  auto* D1 = BI->addDataBlock(Ctx, 1, 10);
  auto* D2 = BI->addDataBlock(Ctx, 5, 10);

  {
    auto F = M->findDataBlock(Addr(0));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);

    F = M->findDataBlock(Addr(1));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), D1);

    F = M->findDataBlock(Addr(5));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(&*F.begin(), D1);
    EXPECT_EQ(&*(++F.begin()), D2);

    F = M->findDataBlock(Addr(10));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(&*F.begin(), D1);
    EXPECT_EQ(&*(++F.begin()), D2);

    F = M->findDataBlock(Addr(11));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), D2);

    F = M->findDataBlock(Addr(14));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), D2);

    F = M->findDataBlock(Addr(15));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);
  }
}

TEST(Unit_Module, symbolIterationOrder) {
  auto* M = Module::Create(Ctx, nullptr);
  auto* S1 = M->addSymbol(Ctx, Addr(3), "foo");
  auto* S2 = M->addSymbol(Ctx, Addr(2), "bar");
  auto* S3 = M->addSymbol(Ctx, Addr(1), "foo");

  {
    auto F = M->symbols_by_name();
    EXPECT_EQ(std::distance(F.begin(), F.end()), 3);
    auto It = F.begin();
    // symbol_name_iterator returns values in name order but does not specify
    // order for symbols with the same name.
    EXPECT_EQ(&*It++, S2);
    if (&*It == S3) {
      EXPECT_EQ(&*++It, S1);
    } else {
      EXPECT_EQ(&*It++, S1);
      EXPECT_EQ(&*It++, S3);
    }
  }
}

TEST(Unit_Module, findSymbols) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(1), 1);
  auto* B = BI->addCodeBlock(Ctx, 0, 1);

  auto* S1 = M->addSymbol(Ctx, Addr(1), "foo");
  auto* S2 = M->addSymbol(Ctx, B, "bar");
  auto* S3 = M->addSymbol(Ctx, Addr(2), "foo");
  auto* S4 = M->addSymbol(Ctx, B, "baz");

  {
    auto F = M->findSymbols("foo");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    // Order of S1 and S2 is unspecified.
    EXPECT_EQ((std::set<Symbol*>{&*F.begin(), &*std::next(F.begin(), 1)}),
              (std::set<Symbol*>{S1, S3}));
  }

  {
    auto F = M->findSymbols("bar");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S2);
  }

  EXPECT_TRUE(M->findSymbols("notfound").empty());

  {
    auto F = M->findSymbols(Addr(1));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 3);
    // Order of S1, S2, and S4 is unspecified.
    EXPECT_EQ((std::set<Symbol*>{&*F.begin(), &*std::next(F.begin(), 1),
                                 &*std::next(F.begin(), 2)}),
              (std::set<Symbol*>{S1, S2, S4}));
  }

  {
    auto F = M->findSymbols(Addr(2));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S3);
  }

  EXPECT_TRUE(M->findSymbols(Addr(3)).empty());

  {
    auto F = M->findSymbols(Addr(0), Addr(2));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 3);
    // Order of S1, S2, and S4 is unspecified.
    EXPECT_EQ((std::set<Symbol*>{&*F.begin(), &*std::next(F.begin(), 1),
                                 &*std::next(F.begin(), 2)}),
              (std::set<Symbol*>{S1, S2, S4}));
  }

  {
    auto F = M->findSymbols(Addr(0), Addr(5));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 4);
    // Order of S1, S2, and S4 is unspecified. All three should be returned
    // before S3.
    EXPECT_EQ((std::set<Symbol*>{&*F.begin(), &*std::next(F.begin(), 1),
                                 &*std::next(F.begin(), 2)}),
              (std::set<Symbol*>{S1, S2, S4}));
    EXPECT_EQ(&*std::next(F.begin(), 3), S3);
  }

  {
    auto F = M->findSymbols(Addr(10), Addr(25));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);
  }

  {
    auto F = M->findSymbols(*B);
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    // Order of S2 and S4 is unspecified.
    EXPECT_EQ((std::set<Symbol*>{&*F.begin(), &*std::next(F.begin(), 1)}),
              (std::set<Symbol*>{S2, S4}));
  }
}

TEST(Unit_Module, symbolWithoutAddr) {
  auto* M = Module::Create(Ctx, nullptr);
  M->addSymbol(Ctx, "test");
  EXPECT_EQ(M->findSymbols("test").begin()->getName(), "test");
}

TEST(Unit_Module, renameSymbol) {
  auto* M = Module::Create(Ctx, nullptr);
  auto* S1 = M->addSymbol(Ctx, "foo");
  auto* S2 = M->addSymbol(Ctx, Addr(1), "bar");
  auto* S3 = M->addSymbol(Ctx, Addr(2), "bar");

  S1->setName("test1");
  S2->setName("test2");

  {
    auto F = M->findSymbols("foo");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);

    F = M->findSymbols("bar");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S3);

    F = M->findSymbols("test1");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S1);

    F = M->findSymbols("test2");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S2);
  }
  {
    auto F = M->findSymbols(Addr(1));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S2);

    F = M->findSymbols(Addr(2));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S3);
  }
}

TEST(Unit_Module, setReferent) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(0), 5);

  auto* B1 = BI->addCodeBlock(Ctx, 1, 1);
  auto* B2 = BI->addCodeBlock(Ctx, 2, 1);
  auto* B3 = BI->addCodeBlock(Ctx, 3, 1);
  auto* B4 = BI->addCodeBlock(Ctx, 4, 1);
  auto* B5 = BI->addCodeBlock(Ctx, 5, 1);
  auto* S1 = M->addSymbol(Ctx, "foo");
  auto* S2 = M->addSymbol(Ctx, B1, "bar");
  auto* S3 = M->addSymbol(Ctx, B1, "foo");
  auto* S4 = M->addSymbol(Ctx, B2, "bar");

  S1->setReferent(B3);
  S2->setReferent(B4);
  S4->setReferent(B5);

  {
    auto F = M->findSymbols("foo");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(&*F.begin(), S1);
    EXPECT_EQ(&*(++F.begin()), S3);

    F = M->findSymbols("bar");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(&*F.begin(), S2);
    EXPECT_EQ(&*(++F.begin()), S4);
  }

  {
    auto F = M->findSymbols(Addr(1));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S3);

    F = M->findSymbols(Addr(2));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);

    F = M->findSymbols(Addr(3));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S1);

    F = M->findSymbols(Addr(4));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S2);

    F = M->findSymbols(Addr(5));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S4);
  }
}

TEST(Unit_Module, setSymbolAddress) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(0), 5);

  auto* B1 = BI->addCodeBlock(Ctx, 1, 1);
  auto* S1 = M->addSymbol(Ctx, "foo");
  auto* S2 = M->addSymbol(Ctx, B1, "bar");
  auto* S3 = M->addSymbol(Ctx, B1, "bar");

  S1->setAddress(Addr(2));
  S2->setAddress(Addr(3));

  {
    auto F = M->findSymbols("bar");
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(&*F.begin(), S2);
    EXPECT_EQ(&*(++F.begin()), S3);
  }

  {
    auto F = M->findSymbols(Addr(1));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S3);

    F = M->findSymbols(Addr(2));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S1);

    F = M->findSymbols(Addr(3));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(&*F.begin(), S2);
  }
}

TEST(Unit_Module, symbolicExpressions) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(1), 123);

  Symbol* Sym = M->addSymbol(Ctx, "test");
  BI->addSymbolicExpression<SymAddrConst>(0, 0, Sym);
  EXPECT_EQ(std::distance(M->symbolic_expressions_begin(),
                          M->symbolic_expressions_end()),
            1);
}

TEST(Unit_Module, findSymbolicExpressions) {
  auto M = Module::Create(Ctx, nullptr);
  auto S = M->addSection(Ctx, "test");
  auto BI = S->addByteInterval(Ctx, Addr(0), 10);

  auto* S1 = M->addSymbol(Ctx, Addr(1), "foo");
  auto* S2 = M->addSymbol(Ctx, Addr(5), "bar");

  BI->addSymbolicExpression<SymAddrConst>(1, 0, S1);
  BI->addSymbolicExpression<SymAddrConst>(5, 0, S2);

  {
    auto F = M->findSymbolicExpression(Addr(1), Addr(5));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(std::get<SymAddrConst>(*F.begin()).Sym, S1);
  }

  {
    auto F = M->findSymbolicExpression(Addr(1), Addr(6));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 2);
    EXPECT_EQ(std::get<SymAddrConst>(*F.begin()).Sym, S1);
    EXPECT_EQ(std::get<SymAddrConst>(*++F.begin()).Sym, S2);
  }

  {
    auto F = M->findSymbolicExpression(Addr(1), Addr(3));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 1);
    EXPECT_EQ(std::get<SymAddrConst>(*F.begin()).Sym, S1);
  }

  {
    auto F = M->findSymbolicExpression(Addr(6), Addr(50));
    EXPECT_EQ(std::distance(F.begin(), F.end()), 0);
  }
}

// TEST(Unit_Module, getAddrsForSymbolicExpression) {
//   auto* M = Module::Create(Ctx, nullptr);
//   SymAddrConst SAC1{0, Symbol::Create(Ctx, Addr(1), "foo")};
//   SymAddrConst SAC2{0, Symbol::Create(Ctx, Addr(5), "bar")};
//   SymAddrConst SAC3{0, Symbol::Create(Ctx, Addr(10), "baz")};

//   M->addSymbolicExpression(Addr(1), SAC1);
//   M->addSymbolicExpression(Addr(5), SAC2);
//   M->addSymbolicExpression(Addr(10), SAC1);
//   // Note: SAC3 is purposefully not added to the module while SAC1 is added
//   // twice at different addresses.

//   {
//     auto R = M->getAddrsForSymbolicExpression(SAC1);
//     EXPECT_EQ(std::distance(R.begin(), R.end()), 2);
//     // The order of the results is not guaranteed, so check that both of the
//     // addresses are present but without relying on order.
//     ptrdiff_t Count = std::count_if(R.begin(), R.end(), [](Addr A) {
//       return A == Addr{10} || A == Addr{1};
//     });
//     EXPECT_EQ(Count, 2);
//   }

//   {
//     auto R = M->getAddrsForSymbolicExpression(SAC2);
//     EXPECT_EQ(std::distance(R.begin(), R.end()), 1);
//     EXPECT_EQ(*R.begin(), Addr{5});
//   }

//   {
//     auto R = M->getAddrsForSymbolicExpression(SAC3);
//     EXPECT_EQ(std::distance(R.begin(), R.end()), 0);
//   }
// }

TEST(Unit_Module, protobufRoundTrip) {
  proto::Module Message;

  UUID BlockID, DataID, ProxyID, SectionID;
  size_t WhichSymbolic;

  {
    Context InnerCtx;
    Module* Original = Module::Create(InnerCtx, nullptr, "module");
    Original->setBinaryPath("test");
    Original->setPreferredAddr(Addr(3));
    Original->setRebaseDelta(4);
    Original->setFileFormat(FileFormat::ELF);
    Original->setISAID(ISAID::X64);
    Original->addAuxData("test", AuxData());
    Original->addSymbol(InnerCtx, Addr(1), "name1");
    Original->addSymbol(InnerCtx, Addr(2), "name1");
    Original->addSymbol(InnerCtx, Addr(1), "name3");
    auto S = Original->addSection(InnerCtx, "test");
    auto BI = S->addByteInterval(InnerCtx, Addr(1), 2);
    BI->addCodeBlock(InnerCtx, 0, 2);
    BI->addDataBlock(InnerCtx, 0, 2);
    auto* P = Original->addProxyBlock(InnerCtx);
    BI->addSymbolicExpression<SymAddrConst>(7);
    BlockID = blocks(Original->getCFG()).begin()->getUUID();
    DataID = Original->data_blocks_begin()->getUUID();
    ProxyID = P->getUUID();
    SectionID = Original->section_begin()->getUUID();
    WhichSymbolic = Original->symbolic_expressions_begin()->index();

    Original->toProtobuf(&Message);
  }

  Module* Result = Module::fromProtobuf(Ctx, nullptr, Message);

  EXPECT_EQ(Result->getBinaryPath(), "test");
  EXPECT_EQ(Result->getPreferredAddr(), Addr(3));
  EXPECT_EQ(Result->getRebaseDelta(), 4);
  EXPECT_EQ(Result->getFileFormat(), FileFormat::ELF);
  EXPECT_EQ(Result->getISAID(), ISAID::X64);
  EXPECT_EQ(Result->getName(), "module");

  // Make sure all symbols are present despite repeated names and addresses.
  EXPECT_EQ(std::distance(Result->symbol_begin(), Result->symbol_end()), 3);
  {
    auto Found = Result->findSymbols("name1");
    EXPECT_EQ(distance(Found.begin(), Found.end()), 2);
  }
  {
    auto Found = Result->findSymbols(Addr(1));
    EXPECT_EQ(distance(Found.begin(), Found.end()), 2);
  }

  // Make sure various collections and node members are serialized, but
  // don't check in detail as they have their own unit tests.
  EXPECT_EQ(Result->getAuxDataSize(), 1);
  EXPECT_NE(Result->getAuxData("test"), nullptr);

  EXPECT_EQ(num_vertices(Result->getCFG()), 2);
  {
    auto Nodes = nodes(Result->getCFG());
    auto It = Nodes.begin();
    EXPECT_TRUE(&*It);
    EXPECT_TRUE(It->getUUID() == BlockID || It->getUUID() == ProxyID);
    ++It;
    EXPECT_TRUE(&*It);
    EXPECT_NE(Nodes.begin()->getUUID(), It->getUUID());
    EXPECT_TRUE(It->getUUID() == BlockID || It->getUUID() == ProxyID);
  }

  EXPECT_EQ(
      std::distance(Result->data_blocks_begin(), Result->data_blocks_end()), 1);
  EXPECT_EQ(Result->data_blocks_begin()->getUUID(), DataID);

  EXPECT_EQ(std::distance(Result->section_begin(), Result->section_end()), 1);
  EXPECT_EQ(Result->section_begin()->getUUID(), SectionID);

  EXPECT_EQ(std::distance(Result->symbolic_expressions_begin(),
                          Result->symbolic_expressions_end()),
            1);
  EXPECT_EQ(Result->symbolic_expressions_begin()->index(), WhichSymbolic);
}

TEST(Unit_Module, protobufNodePointers) {
  // Ensure that deserialization handles node pointers (e.g. in Symbol and
  // SymbolicExpression) correctly.
  // This is order-dependent: the pointers are serialized as UUIDs, and
  // Node::getByUUID will fail if the corresponding Node has not yet been
  // deserialized.

  proto::Module Message;

  {
    Context InnerCtx;
    Module* Original = Module::Create(InnerCtx, nullptr);
    auto S = Original->addSection(InnerCtx, "test");
    auto BI = S->addByteInterval(InnerCtx, Addr(1), 2);
    auto* Data = BI->addDataBlock(InnerCtx, 0, 0);
    auto* DataSym = Original->addSymbol(InnerCtx, Data, "data");

    // Not part of IR
    auto* DanglingData = DataBlock::Create(InnerCtx, nullptr, 0);
    Original->addSymbol(InnerCtx, DanglingData, "dangling");

    auto* Code = BI->addCodeBlock(InnerCtx, 0, 2);
    Original->addSymbol(InnerCtx, Code, "code");
    BI->addSymbolicExpression<SymAddrConst>(2, 0, DataSym);

    // Not part of IR
    auto* DanglingSym = Symbol::Create(InnerCtx, nullptr, Addr(1), "foo");
    BI->addSymbolicExpression<SymAddrConst>(3, 0, DanglingSym);

    Original->toProtobuf(&Message);
  }

  Module* Result = Module::fromProtobuf(Ctx, nullptr, Message);
  EXPECT_NE(Result->findSymbols("data").begin()->getReferent<DataBlock>(),
            nullptr);
  EXPECT_NE(Result->findSymbols("code").begin()->getReferent<CodeBlock>(),
            nullptr);
  // Dangling reference becomes nullptr
  EXPECT_EQ(Result->findSymbols("dangling").begin()->getReferent<CodeBlock>(),
            nullptr);

  const auto& Symbolic =
      get<SymAddrConst>(*Result->findSymbolicExpression(Addr(3)));
  EXPECT_NE(Symbolic.Sym, nullptr);
  EXPECT_EQ(Symbolic.Sym->getName(), "data");

  // Dangling reference becomes nullptr
  EXPECT_EQ(get<SymAddrConst>(*Result->findSymbolicExpression(Addr(4))).Sym,
            nullptr);
}
