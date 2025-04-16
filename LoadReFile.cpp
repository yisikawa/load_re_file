#include "LoadReFile.h"

using namespace irr;
using namespace scene;
using namespace gui;

// Ensure MyEventReceiver inherits from irr::IEventReceiver
class MyEventReceiver : public irr::IEventReceiver {
public:
   virtual bool OnEvent(const SEvent& event) override {
       // Handle events here
       return false;
   }
};

int main()
{
	IrrlichtDevice* gDevice = nullptr;
	io::IFileSystem* FileSystem;
	core::stringc gExportPath = "";
	// Ensure gReceiver is of type MyEventReceiver
	MyEventReceiver gReceiver;
	gExportPath = "Z:\\RedExports";
	auto WindowWidth = 1280;
	auto WindowHeight = 720;



	gDevice = createDevice(video::EDT_DIRECT3D9,
		core::dimension2d<u32>(WindowWidth, WindowHeight),
		16, false, false, false, &gReceiver);
	if (gDevice == 0)
       return 1; // could not create selected driver
	FileSystem = gDevice->getFileSystem();
	gDevice->setResizable(true);
	gDevice->getSceneManager()->getParameters()->setAttribute("RED_EXPORT_PATH", gExportPath.c_str());
	io::IReadFile* bufferFile = FileSystem->createAndOpenFile("idle01.re");
	if (!bufferFile) return false;
	bufferFile->seek(12);
	while (gDevice->run() && gDevice->getVideoDriver())
	{
	   if (gDevice->isWindowActive())
	   {
		   gDevice->getVideoDriver()->beginScene(true, true, video::SColor(255, 100, 101, 140));

		   gDevice->getSceneManager()->drawAll();
		   gDevice->getGUIEnvironment()->drawAll();

		   gDevice->getVideoDriver()->endScene();

	   }
	   else
		   gDevice->yield();
	}
	bufferFile->drop();
	gDevice->drop();
}
