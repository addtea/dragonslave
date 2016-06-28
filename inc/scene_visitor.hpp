#pragma once

namespace dragonslave {


class SceneEntity;
class SceneCamera;
class SceneGroup;
class SceneLight;


class SceneVisitor
{
public:
    virtual ~SceneVisitor() { }

    virtual void visit(SceneCamera* camera) { }
    virtual void visit(SceneEntity* entity) { }
    virtual void visit(SceneGroup* group) { }
    virtual void visit(SceneLight* light) { }
};


}
