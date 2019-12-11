#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::load(Hash<Movie> *hashRatings, Hash<User> *hashUsers, Hash<Tag> *hashTags, Hash<Genre> *hashGenres, Trie *trieMovies, ClearString *cl){
    this->hashTags = hashTags;
    this->hashRatings = hashRatings;
    this->hashUsers = hashUsers;
    this->hashGenres = hashGenres;
    this->trieMovies = trieMovies;
    this->cl = cl;
}

void MainWindow::on_pushButton_clicked(){
    ui->tableWidget->model()->removeRows(0,ui->tableWidget->model()->rowCount());

    if(ui->radioButton->isChecked())
        tag();
    else if(ui->radioButton_2->isChecked())
        user();
    else if(ui->radioButton_3->isChecked())
        movie();
    else if(ui->radioButton_4->isChecked())
        genre();
}

void MainWindow::movie(){
    ui->tableWidget->setColumnCount(5);
    QList<QString> list = {"ID","Title","Genres", "Av. Rating", "Rating Count"};
    ui->tableWidget->setHorizontalHeaderLabels(list);

    QString busca = ui->lineEdit->text();

    vector<Movie*> movies = trieMovies->searchPrefix(cl->clear_string(busca.toStdString()));

    for(int i=0; i<movies.size(); i++){
        cout << movies[i]->toString() << endl;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QString id = QString::fromStdString(to_string(movies[i]->id));
        QString name = QString::fromStdString(movies[i]->name);
        QString genres;
        QString avrating = QString::fromStdString(to_string(movies[i]->num_ratings > 0 ? movies[i]->sum_ratings/movies[i]->num_ratings : 0));
        QString counting = QString::fromStdString(to_string(movies[i]->num_ratings));

        int j;
        for(j=0; j < movies[i]->genres.size() - 1; j++){
            genres += QString::fromStdString(movies[i]->genres[j] + "|");
        }
        genres += QString::fromStdString(movies[i]->genres[j]);

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(id));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(name));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(genres));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(avrating));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(counting));
    }
}

void MainWindow::user(){
    ui->tableWidget->setColumnCount(4);
    QList<QString> list = {"Title", "User Rating", "Av. Global Rating", "Rating Count"};
    ui->tableWidget->setHorizontalHeaderLabels(list);

    int user_id = ui->lineEdit->text().toInt();

    if(hashUsers->search(user_id)){
        vector<pair<Movie*, double>> moviesPair = (*hashUsers)[user_id]->ratings;

        for(int i=0; i < (int) moviesPair.size(); i++){
            Movie *movie = moviesPair[i].first;

            QString name = QString::fromStdString(movie->name);
            QString userrating = QString::fromStdString(to_string(moviesPair[i].second));
            QString avrating = QString::fromStdString(to_string(movie->num_ratings > 0 ? movie->sum_ratings/movie->num_ratings : 0));
            QString counting = QString::fromStdString(to_string(movie->num_ratings));

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(name));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(userrating));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(avrating));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(counting));
        }
    } else {
        cout << "not found motherfucker" << endl;
    }

}

void MainWindow::genre(){
    ui->tableWidget->setColumnCount(4);
    QList<QString> list = {"Title","Genres", "Av. Rating", "Rating Count"};
    ui->tableWidget->setHorizontalHeaderLabels(list);
/*
    string genre = ui->lineEdit->text().toStdString();

    if(hashGenres->search(genre)){
        vector<Movie*> moviesPair = (*hashGenres)[genre]->movies;

        for(int i=0; i < (int) moviesPair.size(); i++){
            Movie *movie = moviesPair[i];

            QString name = QString::fromStdString(movie->name);
            QString userrating = QString::fromStdString("");
            QString avrating = QString::fromStdString(to_string(movie->num_ratings > 0 ? movie->sum_ratings/movie->num_ratings : 0));
            QString counting = QString::fromStdString(to_string(movie->num_ratings));

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(name));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(userrating));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(avrating));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(counting));
        }
    } else {
        cout << "not found motherfucker" << endl;
    }*/

}


void MainWindow::tag(){
    ui->tableWidget->setColumnCount(4);
    QList<QString> list = {"Title", "Genres", "Av. Rating", "Rating Count"};
    ui->tableWidget->setHorizontalHeaderLabels(list);

    QStringList tags = ui->lineEdit->text().split("\"");

    for(int i=0; i < tags.size(); i++){
        if(tags[i].trimmed() == ""){
            tags.removeAt(i);
            --i;
        }
    }

    vector<Movie*> ans;

    if(hashTags->search(cl->clear_string(tags[0].toStdString()))){
        ans = (*hashTags)[cl->clear_string(tags[0].toStdString())]->movies;

        for(int i=1; i < (int)tags.size(); i++){

            if(hashTags->search(cl->clear_string(tags[i].toStdString()))){
                ans = (*hashTags)[cl->clear_string(tags[i].toStdString())]->getIntersection(ans);
            } else {
                ans.clear();
                break;
            }
        }
    }

    if(ans.size() > 0){

        for(int i=0; i < (int) ans.size(); i++){
            Movie *movie = ans[i];

            QString name = QString::fromStdString(movie->name);
            QString genres;
            QString avrating = QString::fromStdString(to_string(movie->num_ratings > 0 ? movie->sum_ratings/movie->num_ratings : 0));
            QString counting = QString::fromStdString(to_string(movie->num_ratings));
            int j;
            for(j=0; j < movie->genres.size()-1; j++){
                genres += QString::fromStdString(movie->genres[j]) + "|";
            }
            genres += QString::fromStdString(movie->genres[j]);

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(name));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(genres));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(avrating));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(counting));
        }
    } else {
        cout << "not found motherfucker" << endl;
    }
}
