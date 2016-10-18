//
// Created by antoinewdg on 10/18/16.
//

#ifndef OPENCV_ADVANCED_IMSHOW_ZOOM_MANAGER_H_H
#define OPENCV_ADVANCED_IMSHOW_ZOOM_MANAGER_H_H

#include <SFML/Graphics.hpp>

namespace oai {
    /**
     * Enables zooming on mouse wheel movement.
     */
    class ZoomManager {
    public:
        ZoomManager(sf::RenderWindow &target, sf::View &image_view) :
                m_window(target), m_image_view(image_view) {}

        inline void on_mouse_wheel_scroll_up(const sf::Event::MouseWheelScrollEvent &scroll_e) {
            auto m = m_window.mapPixelToCoords(sf::Vector2i(scroll_e.x, scroll_e.y), m_image_view);
            float alpha = 1.f - 0.2f * scroll_e.delta;
            auto new_center = m + alpha * (m_image_view.getCenter() - m);

            m_image_view.zoom(alpha);
            m_image_view.setCenter(new_center);
        }

    private:
        sf::RenderWindow &m_window;
        sf::View &m_image_view;
    };
}

#endif //OPENCV_ADVANCED_IMSHOW_ZOOM_MANAGER_H_H
