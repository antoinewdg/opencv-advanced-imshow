//
// Created by antoinewdg on 10/18/16.
//

#ifndef OPENCV_ADVANCED_IMSHOW_DRAG_MANAGER_H
#define OPENCV_ADVANCED_IMSHOW_DRAG_MANAGER_H

#include <SFML/Graphics.hpp>

namespace oai {
    /**
     * Enables user to drag the view with the mouse.
     */
    class DragManager {
    public:
        DragManager(sf::RenderWindow &window, sf::View &image_view) :
                m_window(window), m_image_view(image_view),
                m_dragging(false) {}

        inline void on_mouse_left_pressed(const sf::Event::MouseButtonEvent &button_e) {
            m_dragging = true;
            m_origin_view = m_image_view;
            m_origin_mouse_p = sf::Vector2i(button_e.x, button_e.y);
        }

        inline void on_mouse_left_released(const sf::Event::MouseButtonEvent &button_e) {
            m_dragging = false;
        }

        inline void on_mouse_move(const sf::Event::MouseMoveEvent &move_e) {
            if (m_dragging) {
                auto mouse_p = sf::Vector2i(move_e.x, move_e.y);
                m_image_view = m_origin_view;
                sf::Vector2f p = m_window.mapPixelToCoords(mouse_p, m_origin_view);
                sf::Vector2f o = m_window.mapPixelToCoords(m_origin_mouse_p, m_origin_view);

                m_image_view.setCenter(m_image_view.getCenter() + o - p);

            }
        }


    private:
        sf::RenderWindow &m_window;
        bool m_dragging;
        sf::Vector2i m_origin_mouse_p;
        sf::View m_origin_view;
        sf::View &m_image_view;
    };
}

#endif //OPENCV_ADVANCED_IMSHOW_DRAG_MANAGER_H
