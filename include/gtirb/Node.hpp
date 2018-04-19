#pragma once

#include <boost/uuid/uuid.hpp>
#include <functional>
#include <gtirb/LocalProperties.hpp>
#include <gtirb/Table.hpp>
#include <memory>
#include <string>
#include <vector>

namespace gtirb
{
    ///
    /// \class Node
    /// \author John E. Farrier
    ///
    /// Copied Node objects will copy the references to the Table pointers they own.  This means
    /// that any tables owned by this node will now have at least two owners.
    ///
    class GTIRB_GTIRB_EXPORT_API Node : public LocalProperties
    {
    public:
        ///
        /// A custom STL-compatible iterator for Node children.
        ///
        class iterator
        {
        public:
            typedef iterator self_type;
            typedef gtirb::Node* const value_type;
            typedef gtirb::Node* const reference;
            typedef gtirb::Node* const pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef int difference_type;

            iterator(std::vector<std::shared_ptr<Node>>::iterator x) : it(x)
            {
            }

            self_type operator++()
            {
                self_type i = *this;
                this->it++;
                return i;
            }

            self_type operator++(int)
            {
                this->it++;
                return *this;
            }

            reference operator*()
            {
                return this->it->get();
            }

            pointer operator->()
            {
                return this->it->get();
            }

            bool operator==(const self_type& rhs) const
            {
                return this->it == rhs.it;
            }

            bool operator!=(const self_type& rhs) const
            {
                return this->it != rhs.it;
            }

        private:
            std::vector<std::shared_ptr<Node>>::iterator it;
        };

        ///
        /// A custom STL-compatible const_iterator for Node children.
        ///
        class const_iterator
        {
        public:
            typedef const_iterator self_type;
            typedef gtirb::Node* const value_type;
            typedef gtirb::Node* const reference;
            typedef gtirb::Node* const pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef int difference_type;

            const_iterator(std::vector<std::shared_ptr<Node>>::const_iterator x) : it(x)
            {
            }

            self_type operator++()
            {
                self_type i = *this;
                this->it++;
                return i;
            }

            self_type operator++(int)
            {
                this->it++;
                return *this;
            }

            const reference operator*()
            {
                return this->it->get();
            }

            const pointer operator->()
            {
                return this->it->get();
            }

            bool operator==(const self_type& rhs) const
            {
                return this->it == rhs.it;
            }

            bool operator!=(const self_type& rhs) const
            {
                return this->it != rhs.it;
            }

        private:
            std::vector<std::shared_ptr<Node>>::const_iterator it;
        };

        ///
        /// Automatically assigns the Node a UUID.
        ///
        Node();

        ///
        /// This will serve as a base class for other nodes.
        /// The destructor is trivial and defaulted.
        ///
        virtual ~Node() = default;

        ///
        /// Get a pointer to the Node that owns this Node.
        ///
        /// This is not called "parent" because many node classes will want to use a "parent" type
        /// of relationship.
        ///
        gtirb::Node* const getNodeParent() const;

        ///
        /// Generate and assign a new Universally Unique ID (UUID).
        ///
        /// Though automatically assigned on construction, it can be manually set.
        ///
        void setUUID();

        ///
        /// Manually assign Universally Unique ID (UUID).
        ///
        /// Though automatically assigned on construction, it can be manually set.
        ///
        void setUUID(boost::uuids::uuid x);

        ///
        /// Retrieve the Node's Universally Unique ID (UUID).
        ///
        boost::uuids::uuid getUUID() const;

        ///
        /// Checks to see if 'x' can be a parent of this node.
        ///
        bool getIsValidParent(const Node* const x) const;

        ///
        /// Adds a child node.
        ///
        /// API is modeled after the STL.  Executes functions added via
        /// Node::addPushBackValidator().  Will not add the Node if the Node's validator returns
        /// false.
        ///
        /// Throws gtirb::NodeStructureError.
        ///
        void push_back(std::unique_ptr<gtirb::Node>&& x);

        ///
        /// Determines if there are any child nodes.
        ///
        /// API is modeled after the STL.
        ///
        /// \return     True of there are not any child nodes.
        ///
        bool empty() const;

        ///
        /// Returns the number of elements in the container.
        /// The number of child nodes.  API is modeled after the STL.  Constant complexity.
        ///
        /// \return     Zero for an empty structure, or the number of child nodes.
        ///
        size_t size() const;

        ///
        /// Clear all children from this node.
        ///
        /// API is modeled after the STL.
        ///
        void clear();

        ///
        /// Access specified element with bounds checking.
        ///
        /// \param      x   The position of the element to return.
        /// \return     A pointer to the Node child at the given index.
        ///
        Node* const at(size_t x);

        ///
        /// Access specified element with bounds checking.
        ///
        /// \param      x   The position of the element to return.
        /// \return     A const pointer to the Node child at the given index.
        ///
        const Node* const at(size_t x) const;

        ///
        /// Returns a Node::iterator to the first child Node.
        ///
        /// If the container is empty, the returned iterator will be equal to end().
        ///
        /// \return     An iterator to the first child Node.
        ///
        Node::iterator begin();

        ///
        /// Returns a Node::iterator to the element following the last element of the container.
        ///
        /// This element acts as a placeholder; attempting to access it results in undefined
        /// behavior.
        ///
        /// \return     An iterator to the element following the last element of the container.
        ///
        Node::iterator end();

        ///
        /// Returns a Node::const_iterator to the first child Node.
        ///
        /// If the container is empty, the returned iterator will be equal to end().
        ///
        /// \return     An iterator to the first child Node.
        ///
        Node::const_iterator begin() const;

        ///
        /// Returns a Node::const_iterator to the element following the last element of the
        /// container.
        ///
        /// This element acts as a placeholder; attempting to access it results in undefined
        /// behavior.
        ///
        /// \return     An iterator to the element following the last element of the container.
        ///
        Node::const_iterator end() const;

    protected:
        // ----------------------------------------------------------------------------------------
        // Table Properties

        ///
        /// Locally ownership of a table.
        /// The table can be populated from anywhere.
        ///
        /// This is used to manage Table pointers.  Derived node types should expose
        /// specific functions for the tables that they own or want to provide access to.
        /// They should then return strongly typed pointers to those tables.
        ///
        /// \param name     The name to assign to the table so it can be found later.
        /// \param x        An owning pointer to the table itself.
        ///
        void addTable(std::string name, std::unique_ptr<gtirb::Table>&& x);

        ///
        /// A table by name.
        ///
        /// This is used to manage Table pointers.  Derived node types should expose
        /// specific functions for the tables that they own or want to provide access to.
        /// They should then return strongly typed pointers to those tables.
        ///
        /// Throws std::out_of_range if the container does not have an element with the specified
        /// key. This will search up the node hierarchy until the table is found or the top node is
        /// reached.
        ///
        /// \param  x   The name of the table to search for.
        /// \return     A pointer to the table if found, or nullptr.
        ///
        gtirb::Table* const getTable(const std::string& x) const;

        ///
        /// Remove a table.
        ///
        /// This is used to manage Table pointers.  Derived node types should expose
        /// specific functions for the tables that they own or want to provide access to.
        /// They should then return strongly typed pointers to those tables.
        ///
        /// This will invalidate any pointers that may have been held externally.
        ///
        /// \param  x   The name of the table to search for.
        /// \return     True on success.
        ///
        bool removeTable(const std::string& x);

        ///
        /// Get the total number of tables at this Node.
        ///
        /// This is used to manage Table pointers.  Derived node types should expose
        /// specific functions for the tables that they own or want to provide access to.
        /// They should then return strongly typed pointers to those tables.
        ///
        /// This does not search up the tree.  This is the number of locally owned tables.
        ///
        /// \return     The total number of tables this node owns.
        ///
        size_t getTableSize() const;

        ///
        /// Test to see if the number of tables at this Node is zero.
        ///
        /// This is used to manage Table pointers.  Derived node types should expose
        /// specific functions for the tables that they own or want to provide access to.
        /// They should then return strongly typed pointers to those tables.
        ///
        /// This does not search up the tree.  This is based on locally owned tables.
        ///
        /// \return     True if this node owns at least one table.
        ///
        bool getTablesEmpty() const;

        ///
        /// Clear all locally owned tables.
        ///
        /// This is used to manage Table pointers.  Derived node types should expose
        /// specific functions for the tables that they own or want to provide access to.
        /// They should then return strongly typed pointers to those tables.
        ///
        void clearTables();

        ///
        /// Add a function to validate a parent relationship.
        ///
        /// Derived types should call this in their constructors.
        ///
        void addParentValidator(std::function<bool(const Node* const)> x);

    private:
        gtirb::Node* nodeParent{nullptr};
        boost::uuids::uuid uuid;
        std::map<std::string, std::shared_ptr<gtirb::Table>> tables;
        std::vector<std::function<bool(const Node* const)>> parentValidators;
        std::vector<std::shared_ptr<Node>> children;
    };
} // namespace gtirb