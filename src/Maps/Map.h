/**
 *  @file
 *  @ingroup map
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <Dynamics/b2Body.h>
#include <Dynamics/b2World.h>
#include <ObjectManager.h>


#include <RealVec.h>
#include <Texture.h>
#include <Object.h>
#include <CheckPoint.h>

/**
 * Map class.
 * Contains "physical dimensions".
 * It defines pixel/meters scale.
 */
class Map : public Drawable {
public:
    Map(std::string name, std::string description, RealVec size, TexturePtr view, TexturePtr friction,
        std::vector<CheckPointPtr> &&checkpoints, std::vector<ObjectPtr>
        &&objects);

    float GetPixMetersScale() const;

    float GetFrictionModifier(const RealVec& pos);

    virtual void Draw(RenderWindowPtr window) const;

    std::vector<CheckPointPtr> GetCheckpoints() const;

    void SetStartPosition(sf::Vector2f pos); // TODO move to other place

    sf::Vector2f GetStartPosition() const;

    const sf::View &GetCameraView() const;

    void AlignCameraViewSize(const sf::Window &window);

    void SetCameraViewPosition(const sf::Vector2f &pos);

    void SetCameraViewZoom(float f);

    //void RenderBottomLayer(sf::RenderWindow &window);

    //sf::Sprite &GetMinimap();
    // TODO add minimap
    //sf::Vector2f GetMapSize();
private:
    std::string mapName_;
    std::string mapDescription_;
    sf::View camera_;

    RealVec mapSize_;

    sf::Image imageFriction_;
    sf::Sprite mapView_;
    sf::Vector2f startPosition_;

    std::vector<ObjectPtr> objects_;
    std::vector<CheckPointPtr> checkpoints_;

    float scalePixMeters_;
};

using MapPtr = std::shared_ptr<Map>;
