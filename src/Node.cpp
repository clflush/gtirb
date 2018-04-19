#include <boost/uuid/uuid_generators.hpp>
#include <gtirb/Node.hpp>
#include <gtirb/NodeStructureError.hpp>

using namespace gtirb;

// UUID construction is a bottleneck in the creation of Node.  (~0.5ms)
Node::Node() : uuid(boost::uuids::random_generator()())
{
    this->addParentValidator([this](const Node* const x) {
        // We should not become a parent to ourself.
        if(x->getUUID() != this->getUUID())
        {
            // Search all the way up just to make sure there isn't a circular reference.
            if(this->getNodeParent() != nullptr)
            {
                return this->getNodeParent()->getIsValidParent(x);
            }

            // We are the root and all is still valid.
            return true;
        }

        // Circular reference detected.
        return false;
    });
}

Node* const Node::getNodeParent() const
{
    return this->nodeParent;
}

void Node::setUUID()
{
    this->uuid = boost::uuids::random_generator()();
}

void Node::setUUID(boost::uuids::uuid x)
{
    this->uuid = x;
}

boost::uuids::uuid Node::getUUID() const
{
    return this->uuid;
}

bool Node::getIsValidParent(const Node* const x) const
{
    for(const auto& i : this->parentValidators)
    {
        if(i(x) == false)
        {
            return false;
        }
    }

    return true;
}

void Node::push_back(std::unique_ptr<gtirb::Node>&& x)
{
    assert(x->getNodeParent() == nullptr);

    if(x->getIsValidParent(this) == true)
    {
        x->nodeParent = this;
        this->children.push_back(std::move(x));
    }
    else
    {
        throw gtirb::NodeStructureError("Invalid parent/child relationship.", __FILE__, __LINE__);
    }
}

bool Node::empty() const
{
    return this->children.empty();
}

size_t Node::size() const
{
    return this->children.size();
}

void Node::clear()
{
    this->children.clear();
}

void Node::addTable(std::string name, std::unique_ptr<gtirb::Table>&& x)
{
    this->tables[std::move(name)] = std::move(x);
}

gtirb::Table* const Node::getTable(const std::string& x) const
{
    const auto found = this->tables.find(x);
    if(found != std::end(this->tables))
    {
        return (*found).second.get();
    }

    if(this->nodeParent != nullptr)
    {
        return this->nodeParent->getTable(x);
    }

    return nullptr;
}

bool Node::removeTable(const std::string& x)
{
    const auto found = this->tables.find(x);

    if(found != std::end(this->tables))
    {
        this->tables.erase(found);
        return true;
    }

    return false;
}

size_t Node::getTableSize() const
{
    return this->tables.size();
}

bool Node::getTablesEmpty() const
{
    return this->tables.empty();
}

void Node::clearTables()
{
    this->tables.clear();
}

gtirb::Node* const Node::at(size_t x)
{
    return this->children.at(x).get();
}

const gtirb::Node* const Node::at(size_t x) const
{
    return this->children.at(x).get();
}

Node::iterator Node::begin()
{
    return Node::iterator(std::begin(this->children));
}

Node::iterator Node::end()
{
    return Node::iterator(std::end(this->children));
}

Node::const_iterator Node::begin() const
{
    return Node::const_iterator(std::begin(this->children));
}

Node::const_iterator Node::end() const
{
    return Node::const_iterator(std::end(this->children));
}

void Node::addParentValidator(std::function<bool(const Node* const)> x)
{
    this->parentValidators.push_back(x);
}