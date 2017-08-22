#include "../graphics/Renderer.h"
#include "../misc/WindowsInput.h"
//#include "../input/DXInput.h"
#define OERenderer G::instance()->renderer
#define OEInput G::instance()->input
using namespace OriGraphics;
// G is the global variable holder.
class G{
private:
	G(void);
	static G* _instance;
public:
	static G* instance(void);
	Renderer* renderer;
	WindowsInput* input;
	//DXInput* input;
};