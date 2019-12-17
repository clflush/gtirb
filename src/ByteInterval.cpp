//===- ByteInterval.cpp -----------------------------------------*- C++ -*-===//
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
#include <gtirb/ByteInterval.hpp>
#include <gtirb/Serialization.hpp>
#include <proto/ByteInterval.pb.h>
#include <iterator>

using namespace gtirb;

void ByteInterval::toProtobuf(MessageType* Message) const {
  nodeUUIDToBytes(this, *Message->mutable_uuid());

  if (Address.has_value()) {
    Message->set_has_address(true);
    Message->set_address((uint64_t)*Address);
  } else {
    Message->set_has_address(false);
  }

  Message->set_size(getSize());
  auto bytesIt = Bytes.begin<char>();
  Message->mutable_contents()->reserve(AllocatedSize);
  std::copy(bytesIt, bytesIt + AllocatedSize,
            std::back_inserter(*Message->mutable_contents()));

  for (const auto& block : this->blocks()) {
    auto proto_block = Message->add_blocks();
    auto node = block.getNode();

    proto_block->set_offset(block.getOffset());
    switch (node->getKind()) {
    case Node::Kind::CodeBlock: {
      cast<CodeBlock>(node)->toProtobuf(proto_block->mutable_code());
    } break;
    case Node::Kind::DataBlock: {
      cast<DataBlock>(node)->toProtobuf(proto_block->mutable_data());
    } break;
    default: {
      throw std::runtime_error(
          "unknown Node::Kind in ByteInterval::toProtobuf");
    }
    }
  }

  auto& proto_symbolic_expressions = *Message->mutable_symbolic_expressions();
  for (const auto& pair : this->symbolic_expressions()) {
    proto_symbolic_expressions[pair.first] = gtirb::toProtobuf(pair.second);
  }
}

ByteInterval* ByteInterval::fromProtobuf(Context& C, Section* Parent,
                                         const MessageType& Message) {
  auto addr = Message.has_address() ? std::optional<Addr>{Message.address()}
                                    : std::optional<Addr>{};
  ByteInterval* result = ByteInterval::Create(
      C, Parent, addr, Message.contents().begin(), Message.contents().end(),
      Message.size(), Message.contents().size());

  setNodeUUIDFromBytes(result, Message.uuid());

  for (const auto& proto_block : Message.blocks()) {
    switch (proto_block.value_case()) {
    case proto::Block::ValueCase::kCode: {
      CodeBlock* node = CodeBlock::fromProtobuf(C, result, proto_block.code());
      result->Blocks.emplace(proto_block.offset(), node);
    } break;
    case proto::Block::ValueCase::kData: {
      DataBlock* node = DataBlock::fromProtobuf(C, result, proto_block.data());
      result->Blocks.emplace(proto_block.offset(), node);
    } break;
    default: {
      throw std::runtime_error(
          "unknown Block::ValueCase in ByteInterval::fromProtobuf");
    }
    }
  }
  return result;
}

void ByteInterval::symbolicExpressionsFromProtobuf(Context& C,
                                                   const MessageType& Message) {
  mutateModuleIndices(this, [&]() {
    for (const auto& pair : Message.symbolic_expressions()) {
      SymbolicExpression sym_expr;
      gtirb::fromProtobuf(C, sym_expr, pair.second);
      SymbolicExpressions[pair.first] = sym_expr;
    }
  });
}

ByteVector& gtirb::getByteVector(ByteInterval* BI) { return BI->Bytes; }
const ByteVector& gtirb::getByteVector(const ByteInterval* BI) {
  return BI->Bytes;
}