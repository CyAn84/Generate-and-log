#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test
{
public:
    explicit Test(QString name = "", int width = 0, int height = 0, bool visible = 0);
    virtual ~Test();

    QString name() const;
    void setName(const QString &name);
    int width() const;
    void setWidth(int width);
    int height() const;
    void setHeight(int height);
    bool isVisible() const;
    void setVisible(bool visible);

private:
    QString m_name;
    int m_width;
    int m_height;
    bool m_visible;
};

#endif // TEST_H
