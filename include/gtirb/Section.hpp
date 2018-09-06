#ifndef GTIRB_SECTION_H
#define GTIRB_SECTION_H

#include <gtirb/Addr.hpp>
#include <gtirb/Node.hpp>
#include <cstdint>

namespace proto {
class Section;
}

namespace gtirb {

/// \class Section
///
/// \brief DOCFIXME
class GTIRB_EXPORT_API Section : public Node {
  Section(Context& C) : Node(C, Kind::Section) {}
  Section(Context& C, const std::string& N, Addr A, uint64_t S)
      : Node(C, Kind::Section), Name(N), Address(A), Size(S) {}

public:
  /// \brief Create a Section object in its default state.
  ///
  /// \param C  The Context in which this object will be held.
  ///
  /// \return The newly created object.
  static Section* Create(Context& C) { return new (C) Section(C); }

  /// \brief Create a Section object.
  ///
  /// \param C        The Context in which this object will be held.
  /// \param Name     The name of the section.
  /// \param Address  The initial address of the section.
  /// \param Size     The size of the section, in bytes.
  ///
  /// \return The newly created object.
  static Section* Create(Context& C, const std::string& Name, Addr Address,
                         uint64_t Size) {
    return new (C) Section(C, Name, Address, Size);
  }

  /// \brief Equality operator overload.
  bool operator==(const Section& Other) const;

  /// \brief Inequality operator overload.
  bool operator!=(const Section& Other) const;

  /// \brief Get the name of a Section.
  ///
  /// \return The name.
  const std::string& getName() const { return Name; }

  /// \brief Get the address of a Section
  ///
  /// \return The address.
  const Addr getAddress() const { return Address; }

  /// \brief Get the size of a Section
  ///
  /// \return The size.
  uint64_t getSize() const { return Size; }

  /// \brief DOCFIXME
  using MessageType = proto::Section;

  /// \brief DOCFIXME
  ///
  /// \param Message DOCFIXME
  ///
  /// \return void
  void toProtobuf(MessageType* Message) const;

  /// \brief DOCFIXME
  ///
  /// \param C       DOCFIXME
  /// \param Message DOCFIXME
  ///
  /// \return void
  static Section* fromProtobuf(Context& C, const MessageType& Message);

  static bool classof(const Node* N) { return N->getKind() == Kind::Section; }

private:
  std::string Name;
  Addr Address{0};
  uint64_t Size{0};
};
} // namespace gtirb

#endif // GTIRB_SECTION_H
