#include <GameObjects/CheckPoint/CheckPoint.h>

CheckPoint::CheckPoint(b2Body *body, VisualObjectPtr visualObject)
        : Object(body, visualObject, OBJECT_TYPE_CHECK_POINT){
    body_->SetUserData(this);
}

void CheckPoint::SetObserver(CheckPointObserver *observer) {
    observer_ = observer;
}

void CheckPoint::SetEnable(bool value) {
    enable_ = value;
}

bool CheckPoint::IsEnable() const {
    return enable_;
}

void CheckPoint::BeginContact() {
    if (enable_) {
        enable_ = false;
        if (observer_ != nullptr) {
            observer_->NotifyCheckPointReached();
        }
    }
}

void CheckPoint::Draw(RenderWindowPtr window) {
    if (IsEnable()) {
        Object::Draw(window);
    }
}

void CheckPoint::EndContact() {}

b2Body *CheckPoint::InitializeBody(b2World *world, const RealVec &size) {
    b2BodyDef bodyDef;
    b2Body *body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2(0, 0), 0); // center
    // TODO is size set correct?

    fixtureDef.shape = &polygonShape;
    fixtureDef.isSensor = true;

    body->CreateFixture(&fixtureDef);
    return body;
}

