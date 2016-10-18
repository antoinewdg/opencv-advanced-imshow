//
// Created by antoinewdg on 10/18/16.
//

#ifndef OPENCV_ADVANCED_IMSHOW_RECT_SELECT_MANAGER_H
#define OPENCV_ADVANCED_IMSHOW_RECT_SELECT_MANAGER_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace oai {

    /**
     * Enables user to select a part of the image.
     *
     * When maintaining right click, display a transparent
     * rectangle over the selected area. When the right button
     * is released, print the selected rectangle's characteristics
     * to the standard output.
     */
    class RectSelectManager {
    public:
        RectSelectManager(sf::RenderWindow &window, const sf::View &image_view, std::ostream &out) :
                m_window(window), m_image_view(image_view),
                m_out(out), m_selecting(false) {

            m_rectangle_shape.setFillColor(sf::Color(68, 164, 246, 100));
        }

        void on_mouse_right_pressed(const sf::Event::MouseButtonEvent &button_e) {
            m_selecting = true;
            auto p = sf::Vector2i(button_e.x, button_e.y);
            m_origin = m_window.mapPixelToCoords(p, m_image_view);
            m_rectangle_shape.setPosition(std::floor(m_origin.x), std::floor(m_origin.y));
            m_rectangle_shape.setSize(sf::Vector2f(1.f, 1.f));
        }

        void on_mouse_right_released(const sf::Event::MouseButtonEvent &button_e) {
            m_selecting = false;
            auto p = m_rectangle_shape.getPosition();
            auto q = m_rectangle_shape.getPosition() + m_rectangle_shape.getSize();
            auto s = m_rectangle_shape.getSize();

            m_out << "Rect[" << p.x << ", " << p.y << " ; "
                  << q.x - 1 << ", " << q.y - 1 << "]  "
                  << s.x << "x" << s.y << endl;
        }

        void on_mouse_move(const sf::Event::MouseMoveEvent &move_e) {
            if (m_selecting) {
                auto p = m_window.mapPixelToCoords(sf::Vector2i(move_e.x, move_e.y), m_image_view);
                auto rect = _get_rect(m_origin, p);
                m_rectangle_shape.setPosition(rect.left, rect.top);
                m_rectangle_shape.setSize(sf::Vector2f(rect.width, rect.height));
            }
        }


        void draw(sf::RenderTarget &target) {
            if (m_selecting) {
                target.draw(m_rectangle_shape);
            }
        }


    private:

        sf::FloatRect _get_rect(const sf::Vector2f &a, const sf::Vector2f &b) {
            float xmin = std::floor(std::min(a.x, b.x));
            float xmax = std::ceil(std::max(a.x, b.x));
            float ymin = std::floor(std::min(a.y, b.y));
            float ymax = std::ceil(std::max(a.y, b.y));
            return sf::FloatRect(xmin, ymin, xmax - xmin, ymax - ymin);
        }


        sf::RenderWindow &m_window;
        const sf::View &m_image_view;
        std::ostream &m_out;
        bool m_selecting;
        sf::Vector2f m_origin;
        sf::RectangleShape m_rectangle_shape;
    };
}

#endif //OPENCV_ADVANCED_IMSHOW_RECT_SELECT_MANAGER_H
