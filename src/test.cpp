#include "test.h"

Test::Test(QString name, int width, int height, bool visible)
    : m_name(name)
    , m_width(width)
    , m_height(height)
    , m_visible(visible)
{

}

Test::~Test()
{

}

QString Test::name() const
{
    return m_name;
}

void Test::setName(const QString &name)
{
    m_name = name;
}

int Test::width() const
{
    return m_width;
}

void Test::setWidth(int width)
{
    m_width = width;
}

int Test::height() const
{
    return m_height;
}

void Test::setHeight(int height)
{
    m_height = height;
}

bool Test::isVisible() const
{
    return m_visible;
}

void Test::setVisible(bool visible)
{
    m_visible = visible;
}
