#include "NodeState.hpp"

#include "NodeDataModel.hpp"

NodeState::
NodeState(std::unique_ptr<NodeDataModel> const &model)
  : _outConnections(model->nSlots(PortType::OUT))
  , _inConnections(model->nSlots(PortType::IN))
  , _reaction(NOT_REACTING)
{}

std::vector<std::weak_ptr<Connection> > const&
NodeState::
getEntries(PortType portType) const
{
  Q_ASSERT(portType != PortType::NONE);

  if (portType == PortType::OUT)
    return _outConnections;
  else
    return _inConnections;
}


std::vector<std::weak_ptr<Connection> > &
NodeState::
getEntries(PortType portType)
{
  Q_ASSERT(portType != PortType::NONE);

  if (portType == PortType::OUT)
    return _outConnections;
  else
    return _inConnections;
}


std::shared_ptr<Connection>
NodeState::
connection(PortType portType, PortIndex portIndex) const
{
  auto const &connections = getEntries(portType);

  return connections[portIndex].lock();
}


void
NodeState::
setConnection(PortType portType,
              PortIndex portIndex,
              std::shared_ptr<Connection> connection)
{
  auto &connections = getEntries(portType);

  connections[portIndex] = connection;
}


//void
//NodeState::
//setConnectionId(PortType portType, size_t nEntry, QUuid id)
//{
//std::vector<QUuid> const& entries =
//const_cast<NodeState const&>(*this).getEntries(portType);

//const_cast<std::vector<QUuid>&>(entries)[nEntry] = id;
//}

NodeState::ReactToConnectionState
NodeState::
reaction() const
{
  return _reaction;
}


void
NodeState::
setReaction(ReactToConnectionState reaction)
{
  _reaction = reaction;
}


bool
NodeState::
isReacting() const
{
  return _reaction == REACTING;
}
