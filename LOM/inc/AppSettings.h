#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QMap>
#include <QString>
#include <QObject>

class AppSettings : public QObject {
  /*  Q_OBJECT
public:
    static AppSettings& Instance() {
        static AppSettings s;
        return s;
    }
    static bool Load(QString filemame) {
        QMap<QString, QString> m;
        emit SettingsChanged();
    }

    static bool Save(QString filename) {

    }

    static bool Set(QString key, QString value) {
        emit SettingsChanged();
    }

    static QString Get(QString key) {

    }
signals:
    static void SettingsChanged();
private:
    // Singletone pattern methods.
    AppSettings() {








    }

    ~AppSettings();
    AppSettings(AppSettings const&) = delete;
    AppSettings& operator= (AppSettings const&) = delete;
    static QMap<QString, QString> map;*/
};

#endif // APPSETTINGS_H
