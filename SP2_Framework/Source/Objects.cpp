#include "Objects.h"

Objects::Objects(void)
{
	Mesh* mesh = NULL;
	pos.Set(0, 0, 0);
	render = true;
	reflectLight = true;
	obj = OBJ_MISCE;
	parentObj = NULL;
}

Objects::~Objects(void)
{

}

void Objects::setAll(Mesh* _mesh, Vector3 _pos, properties _TRS, bool _render, bool _reflectLight, OBJECT_TYPES _obj, Objects *_parentObj)
{
	mesh = _mesh;
	pos = _pos;
	TRS = _TRS;
	render = _render;
	reflectLight = _reflectLight;
	obj = _obj;
	parentObj = _parentObj;
}

void Objects::setMesh(Mesh* _mesh)
{
	mesh = _mesh;
}

Mesh* Objects::getMesh(void) const
{
	return mesh;
}

void Objects::setPos(Vector3 _pos)
{
	pos = _pos;
}

Vector3 Objects::getPos(void) const
{
	return pos;
}

void Objects::setProperties(properties _TRS)
{
	TRS = _TRS;
}

properties Objects::getProperties(void) const
{
	return TRS;
}

void Objects::setRender(bool _render)
{
	render = _render;
}

bool Objects::getRender(void) const
{
	return render;
}

void Objects::setReflectLight(bool _reflectLight)
{
	reflectLight = _reflectLight;
}

bool Objects::getReflectLight(void) const
{
	return reflectLight;
}

void Objects::setOBJ(OBJECT_TYPES _obj)
{
	obj = _obj;
}

OBJECT_TYPES Objects::getOBJ(void) const
{
	return obj;
}

void Objects::setParent(Objects *_parentObj)
{
	parentObj = _parentObj;
}

Objects* Objects::getParentObj(void) const
{
	return parentObj;
}