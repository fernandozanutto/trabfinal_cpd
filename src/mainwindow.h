#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "header/Hash.h"
#include "Hash.cpp"
#include "header/User.h"
#include "header/Movie.h"

#include "header/Trie.h"
#include "header/Tag.h"
#include "header/Genre.h"
#include "header/ClearString.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void load(Hash<Movie> *hashRatings, Hash<User> *hashUsers,
               Hash<Tag> *hashTags, Hash<Genre> *hashGenres, Trie *trieMovies, ClearString *cl);

private slots:
    void on_pushButton_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

    void on_lineEdit_3_returnPressed();

private:
    Ui::MainWindow *ui;
    Hash<Movie> *hashRatings;
    Hash<User> *hashUsers;
    Hash<Tag> *hashTags;
    Hash<Genre> *hashGenres;
    Trie *trieMovies;
    ClearString *cl;

    void tag();
    void user();
    void movie();
    void genre();
};
#endif // MAINWINDOW_H
