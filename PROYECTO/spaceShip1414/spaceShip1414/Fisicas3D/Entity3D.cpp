
#include "Entity3D.h"
#include "Mundo3D.h"
#include "GlDebugDraw.h"


//Entity3D::Entity3D(Mundo3D *mundo, void* dirPers)
//{
//	body = new btCapsuleShape(1.0f, 2.0f);
//	rigidBody = new btRigidBody();
//	
//
//}


//Entity3D::Entity3D(Mundo3D * mundo, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, void * dirPers)
//{
//	m = mundo;
//
//	btCapsuleShape *capsule = new btCapsuleShape(2.0f, 5.0f);
//
//	btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
//		btQuaternion(rot.x, rot.y, rot.z, 1.0f),
//		//btVector3(pos.x, pos.y, pos.z)
//		btVector3(0,0,0)
//
//	));
//
//	btTransform trans(btQuaternion(rot.x, rot.y, rot.z, 1.0f),
//		btVector3(0, 0, 0));
//
//	rigidBody = new btRigidBody(1.0f, motionstate, capsule, btVector3(0, 0, 0));
//	rigidBody->setUserPointer(this);
//	dirObjeto3D = dirPers;
//	live = true;
//	iden = 0;
//	mundo->getMundo3DBullet()->addRigidBody(rigidBody);
//
//	//virtual void drawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color)
//	mundo->getDebgMode()->drawCapsule(2.0f, 2.5f,2 ,trans, btVector3(255, 10, 10));
//}
//
//Entity3D::Entity3D(Mundo3D * mundo, void * dirPared, glm::vec3 pos, glm::vec3 rot, glm::vec3 escala)
//{
//	m = mundo;
//	btBoxShape *box = new btBoxShape(btVector3(escala.x, escala.y, escala.z));
//
//	btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
//		btQuaternion(rot.x, rot.y, rot.z, 1.0f),
//		btVector3(pos.x, pos.y, pos.z)
//	));
//
//	rigidBody = new btRigidBody(0.0f, motionstate, box, btVector3(0, 0, 0));
//	rigidBody->setUserPointer(this);
//	dirObjeto3D = dirPared;
//	live = true;
//	iden = 1;
//	mundo->getMundo3DBullet()->addRigidBody(rigidBody);
//
//}
//
//Entity3D::~Entity3D()
//{
//	m->getMundo3DBullet()->removeRigidBody(rigidBody);
//	rigidBody = nullptr;
//}
//
//void * Entity3D::getObjeto3D()
//{
//	return dirObjeto3D;
//}
//
//btRigidBody * Entity3D::getCuerpo3D()
//{
//	return rigidBody;
//}
//
//int Entity3D::getIDEN()
//{
//	return iden;
//}
//
//bool Entity3D::getLive()
//{
//	return live;
//}
//
//void Entity3D::setLive(bool x)
//{
//	live = x;
//}
