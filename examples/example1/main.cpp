#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowGraphicsView>
#include <nodes/DataModelRegistry>

#include "models.hpp"


static bool
registerDataModels()
{
  DataModelRegistry::registerModel<NaiveDataModel>("NaiveDataModel");

  /*
   We could have more models registered.
   All of them become items in the context meny of the scene.

  DataModelRegistry::registerModel<AnotherDataModel>("AnotherDataModel");
  DataModelRegistry::registerModel<OneMoreDataModel>("OneMoreDataModel");

  */

  return true;
}

static bool registerOK = registerDataModels();


//------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  FlowScene scene;

  FlowGraphicsView view(&scene);

  view.setWindowTitle("Node-based flow editor");
  view.resize(800, 600);
  view.show();

  return app.exec();
}
