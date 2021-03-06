#pragma once

#include <memory>

#include <QtCore/QObject>
#include <QtCore/QUuid>

#include "PortType.hpp"

#include "ConnectionState.hpp"
#include "ConnectionGeometry.hpp"

class Node;
class ConnectionGraphicsObject;
class QPointF;

//------------------------------------------------------------------------------

///
class Connection
{
public:

  /// New Connection is attached to the port of the given Node.
  /// The port has parameters (portType, portIndex).
  /// The opposite connection end will require anothre port.
  Connection(PortType portType,
             std::shared_ptr<Node> node,
             PortIndex portIndex);
  ~Connection();

  QUuid id() const;

  /// Remembers the end being dragged.
  /// Invalidates Node address.
  /// Grabs mouse.
  void setRequiredPort(PortType portType);
  PortType requiredPort() const;

  void setGraphicsObject(std::unique_ptr<ConnectionGraphicsObject>&& graphics);

  /// Assigns a node to the required port.
  /// It is assumed that there is a required port, no extra checks
  void setNodeToPort(std::shared_ptr<Node> node,
                     PortType portType,
                     PortIndex portIndex);

public:

  std::unique_ptr<ConnectionGraphicsObject> const&getConnectionGraphicsObject() const;

  ConnectionState const & connectionState() const;
  ConnectionState& connectionState();

  ConnectionGeometry& connectionGeometry();

  std::weak_ptr<Node> const & getNode(PortType portType) const;
  std::weak_ptr<Node> & getNode(PortType portType);

  PortIndex getPortIndex(PortType portType) const;

  void clearNode(PortType portType);

private:

  QUuid _id;

private:

  std::weak_ptr<Node> _outNode;
  std::weak_ptr<Node> _inNode;

  PortIndex _outPortIndex;
  PortIndex _inPortIndex;

private:

  ConnectionState    _connectionState;
  ConnectionGeometry _connectionGeometry;

  std::unique_ptr<ConnectionGraphicsObject> _connectionGraphicsObject;
};
