#ifndef LEARNINGPATH_H
#define LEARNINGPATH_H

#include <QObject>

using std::string;
using std::vector;

class LearningPath : public QObject
{
    Q_OBJECT

private:
    vector<vector<vector<QString>>> textData;

public:
    explicit LearningPath(QObject *parent = nullptr);
    vector<vector<vector<QString>>> getTextData();

signals:

};

#endif // LEARNINGPATH_H
