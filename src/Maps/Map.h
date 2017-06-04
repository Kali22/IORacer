#pragma once


#include <bits/stdc++.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <RealVec.h>
#include <Texture/Texture.h>
#include <InitialPosition.h>
#include <Drawable.h>
#include <ObjectTypes.h>
#include <Object.h>
#include <InitialPosition.h>
#include <Sprite.h>

/**
 * Map class.
 * Contains "physical dimensions".
 * It defines pixel/meters scale.
 */
class Map : public Drawable {
public:
    Map(std::string name, std::string description, RealVec size, TexturePtr view, TexturePtr friction,
        TexturePtr minimap, std::vector<InitialPosition> checkpoints, std::vector<ObjectPtr> objects,
        std::vector<InitialPosition> standings);

    float GetPixMetersScale() const;

    float GetFrictionModifier(const RealVec &pos);

    virtual void Draw(RenderWindowPtr window) const;

    const std::vector<InitialPosition> & GetCheckpoints() const;

    InitialPosition GetInitialPosition(int position) const;

    TexturePtr GetMinimapTexture() const;

    RealVec GetSize() const;

    std::string GetMapName() const;

private:
    std::string mapName_;
    std::string mapDescription_;

    RealVec mapSize_;

    sf::Image imageFriction_;
    sf::Sprite mapView_;
    TexturePtr minimapTexture_;

    std::vector<InitialPosition> startPositions_;
    std::vector<InitialPosition> checkpoints_;

    std::vector<ObjectPtr> objects_;

    float scalePixMeters_;

    void GetImageAndTexture(TexturePtr view, TexturePtr friction);

    void SetScale(RealVec size);

    void SetOrigin();

    void PrintCreationLog();
};

using MapPtr = std::shared_ptr<Map>;
