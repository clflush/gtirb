//===- IR.cpp ---------------------------------------------------*- C++ -*-===//
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
#include "IR.hpp"
#include "Serialization.hpp"
#include <gtirb/DataObject.hpp>
#include <gtirb/ImageByteMap.hpp>
#include <gtirb/Module.hpp>
#include <gtirb/Section.hpp>
#include <gtirb/Symbol.hpp>
#include <gtirb/SymbolicExpression.hpp>
#include <gtirb/Table.hpp>
#include <proto/IR.pb.h>

using namespace gtirb;

void IR::addTable(const std::string &Name, Table&& X) {
  this->Tables[Name] = std::move(X);
}

const gtirb::Table* IR::getTable(const std::string& X) const {
  auto Found = this->Tables.find(X);
  if (Found != std::end(this->Tables)) {
    return &(Found->second);
  }

  return nullptr;
}

gtirb::Table* IR::getTable(const std::string& X) {
  auto Found = this->Tables.find(X);
  if (Found != std::end(this->Tables)) {
    return &(Found->second);
  }

  return nullptr;
}

bool IR::removeTable(const std::string& X) {
  const auto Found = this->Tables.find(X);

  if (Found != std::end(this->Tables)) {
    this->Tables.erase(Found);
    return true;
  }

  return false;
}

void IR::toProtobuf(MessageType* Message) const {
  nodeUUIDToBytes(this, *Message->mutable_uuid());
  containerToProtobuf(this->Modules, Message->mutable_modules());
  containerToProtobuf(this->Tables, Message->mutable_tables());
}

IR* IR::fromProtobuf(Context& C, const MessageType& Message) {
  auto* I = IR::Create(C);
  setNodeUUIDFromBytes(I, Message.uuid());
  containerFromProtobuf(C, I->Modules, Message.modules());
  containerFromProtobuf(C, I->Tables, Message.tables());
  return I;
}

void IR::save(std::ostream& Out) const {
  MessageType Message;
  this->toProtobuf(&Message);
  Message.SerializeToOstream(&Out);
}

IR* IR::load(Context& C, std::istream& In) {
  MessageType Message;
  Message.ParseFromIstream(&In);
  return IR::fromProtobuf(C, Message);
}
