#include "mainwindow.h"

#include "ui_mainwindow.h"

const string DATAFILE = "../data.txt";

MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), ui(new Ui::MainWindow) {
  ui -> setupUi(this);
  // создаем кнопку
  BinTreeButton = new QPushButton("", this);
  CartTreeButton = new QPushButton("", this);
  AvlTreeButton = new QPushButton("", this);
  RBTreeButton = new QPushButton("", this);
  // устанавливаем размер и положение кнопки
  BinTreeButton -> setGeometry(QRect(QPoint(100, 100), QSize(160, 160)));
  CartTreeButton -> setGeometry(QRect(QPoint(300, 100), QSize(160, 160)));
  AvlTreeButton -> setGeometry(QRect(QPoint(500, 100), QSize(160, 160)));
  RBTreeButton -> setGeometry(QRect(QPoint(700, 100), QSize(160, 160)));
  BinTreeButton -> setStyleSheet("background-color: white");
  CartTreeButton -> setStyleSheet("background-color: white");
  AvlTreeButton -> setStyleSheet("background-color: white");
  RBTreeButton -> setStyleSheet("background-color: white");

  functype = new QComboBox(this);
  functype -> addItem("insert");
  functype -> addItem("find");
  functype -> addItem("erase");
  functype -> setGeometry(QRect(QPoint(750, 350), QSize(80, 30)));

  datatype = new QComboBox(this);
  datatype -> addItem("integer");
  datatype -> addItem("float");
  datatype -> addItem("char");
  datatype -> setGeometry(QRect(QPoint(750, 400), QSize(80, 30)));

  QPixmap BinTreePixmap("../binarytree.jpg");
  QPixmap CartTreePixmap("../carttree.jpg");
  QPixmap AvlTreePixmap("../avltree.jpg");
  QPixmap RBTreePixmap("../rbtree.jpg");
  QIcon BinTreeButtonIcon(BinTreePixmap);
  QIcon CartTreeButtonIcon(CartTreePixmap);
  QIcon AvlTreeButtonIcon(AvlTreePixmap);
  QIcon RBTreeButtonIcon(RBTreePixmap);

  BinTreeButton -> setIcon(BinTreeButtonIcon);
  BinTreeButton -> setIconSize(BinTreeButton -> rect().size() * 0.97);
  CartTreeButton -> setIcon(CartTreeButtonIcon);
  CartTreeButton -> setIconSize(CartTreeButton -> rect().size() * 0.97);
  AvlTreeButton -> setIcon(AvlTreeButtonIcon);
  AvlTreeButton -> setIconSize(AvlTreeButton -> rect().size() * 0.97);
  RBTreeButton -> setIcon(RBTreeButtonIcon);
  RBTreeButton -> setIconSize(RBTreeButton -> rect().size() * 0.97);

  connect(BinTreeButton, SIGNAL(clicked()), this, SLOT(handleButton()));
  connect(CartTreeButton, SIGNAL(clicked()), this, SLOT(handleButton()));
  connect(AvlTreeButton, SIGNAL(clicked()), this, SLOT(handleButton()));
  connect(RBTreeButton, SIGNAL(clicked()), this, SLOT(handleButton()));

  LoadFileButton = new QPushButton("Load File", this);
  LoadFileButton -> setGeometry(QRect(QPoint(750, 450), QSize(80, 30)));
  connect(LoadFileButton, SIGNAL(clicked()), this, SLOT(showFileBrowser()));

  RandomGenerateButton = new QPushButton("Random Data", this);
  RandomGenerateButton -> setGeometry(QRect(QPoint(750, 500), QSize(80, 30)));
  connect(RandomGenerateButton, SIGNAL(clicked()), this, SLOT(generateRandomData()));

  ClearButton = new QPushButton("Clear", this);
  ClearButton -> setGeometry(QRect(QPoint(750, 550), QSize(80, 30)));
  connect(ClearButton, SIGNAL(clicked()), this, SLOT(clear()));

  connect(ui -> pushButton, SIGNAL(clicked()), this, SLOT(testing()));

  QMovie * loading = new QMovie("../loading.gif");
  ui -> label -> setMovie(loading);
  loading -> start();
  ui -> label -> setVisible(false);
}

void MainWindow::testing() {
  ui -> label -> setVisible(true);
  ui -> pushButton -> blockSignals(true);

  QThread * thread = QThread::create([ & ]() {
    test();
    ui -> label -> setVisible(false);
    ui -> pushButton -> blockSignals(false);
  });

  thread -> start();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::handleButton() {
  if (sender() == BinTreeButton) {
    BinButtonPressed = !BinButtonPressed;
    if (BinButtonPressed) BinTreeButton -> setStyleSheet("background-color: yellow");
    else BinTreeButton -> setStyleSheet("background-color: white");
  } else if (sender() == CartTreeButton) {
    CartButtonPressed = !CartButtonPressed;
    if (CartButtonPressed) CartTreeButton -> setStyleSheet("background-color: yellow");
    else CartTreeButton -> setStyleSheet("background-color: white");
  } else if (sender() == AvlTreeButton) {
    AvlButtonPressed = !AvlButtonPressed;
    if (AvlButtonPressed) AvlTreeButton -> setStyleSheet("background-color: yellow");
    else AvlTreeButton -> setStyleSheet("background-color: white");
  } else if (sender() == RBTreeButton) {
    RBButtonPressed = !RBButtonPressed;
    if (RBButtonPressed) RBTreeButton -> setStyleSheet("background-color: yellow");
    else RBTreeButton -> setStyleSheet("background-color: white");
  }

}

void MainWindow::showFileBrowser() {
  QString filename = QFileDialog::getOpenFileName(
    this,
    "File selection",
    "C:\\users\\stani"
  );

  string line;
  ifstream fin(filename.toStdString());
  ofstream fout(DATAFILE);
  if (fin.is_open() and fout.is_open()) {
    fout.clear();
    ui -> plainTextEdit -> clear();

    if (datatype -> currentText().toStdString() == "integer") {
      int k;
      int i = 0;
      while (fin >> k) {
        fout << k;
        fout << " ";

        if (i < 500) {
          ui -> plainTextEdit -> moveCursor(QTextCursor::End);
          ui -> plainTextEdit -> insertPlainText(QString::fromStdString(to_string(k) + " "));
        }
        if (i == 500) {
          ui -> plainTextEdit -> moveCursor(QTextCursor::End);
          ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" ....."));
        }
        ++i;
      }

    } else if (datatype -> currentText().toStdString() == "float") {
      float k;
      int i = 0;
      while (fin >> k) {
        fout << k;
        fout << " ";
        if (i < 500) {
          ui -> plainTextEdit -> moveCursor(QTextCursor::End);
          ui -> plainTextEdit -> insertPlainText(QString::fromStdString(to_string(k) + " "));
        }
        if (i == 500) {
          ui -> plainTextEdit -> moveCursor(QTextCursor::End);
          ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" ....."));
        }
        ++i;
      }
    } else {
      char k;
      int i = 0;
      while (fin >> k) {
        fout << k;
        fout << " ";
        if (i < 500) {
          ui -> plainTextEdit -> moveCursor(QTextCursor::End);
          ui -> plainTextEdit -> insertPlainText(QChar(k));
          ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" "));
        }
        if (i == 500) {
          ui -> plainTextEdit -> moveCursor(QTextCursor::End);
          ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" ....."));
        }
        ++i;
      }
    }

    ui -> plainTextEdit -> setReadOnly(true);
  }
}

vector < int > generate_random_ints(int count, int min, int max) {
  srand(time(NULL));
  vector < int > rand_vector;
  for (int i = 0; i < count; ++i) {
    rand_vector.push_back(min + rand() % (max - min + 1));
  }
  return rand_vector;
}

vector < float > generate_random_floats(int count, int min, int max) {
  srand(time(NULL));
  vector < float > rand_vector;
  for (int i = 0; i < count; ++i) {
    rand_vector.push_back(max + (float) rand() / RAND_MAX * (min - max));
  }
  return rand_vector;
}

vector < char > generate_random_chars(int count) {
  srand(time(NULL));
  vector < char > rand_vector;
  string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  for (int i = 0; i < count; ++i) {
    rand_vector.push_back(chars[rand() % chars.size()]);
  }
  return rand_vector;
}

void MainWindow::generateRandomData() {
  ui -> plainTextEdit -> clear();
  ui -> plainTextEdit -> setReadOnly(true);

  string type = datatype -> currentText().toStdString();
  int count = ui -> spinBox -> text().toInt();

  ofstream fout(DATAFILE);
  fout.clear();
  if (type == "integer") {
    vector < int > rand_vector = generate_random_ints(count, 0, 1000000);
    for (size_t i = 0; i < rand_vector.size(); ++i) {
      fout << rand_vector[i] << " ";
      if (i < 500) {
        ui -> plainTextEdit -> moveCursor(QTextCursor::End);
        ui -> plainTextEdit -> insertPlainText(QString::fromStdString(to_string(rand_vector[i]) + " "));
      }
      if (i == 500) {
        ui -> plainTextEdit -> moveCursor(QTextCursor::End);
        ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" ....."));
      }
    }
  } else if (type == "float") {
    vector < float > rand_vector = generate_random_floats(count, 0, 1000000);
    for (size_t i = 0; i < rand_vector.size(); ++i) {
      fout << rand_vector[i] << " ";
      if (i < 500) {
        ui -> plainTextEdit -> moveCursor(QTextCursor::End);
        ui -> plainTextEdit -> insertPlainText(QString::fromStdString(to_string(rand_vector[i]) + " "));
      }
      if (i == 500) {
        ui -> plainTextEdit -> moveCursor(QTextCursor::End);
        ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" ....."));
      }
    }
  } else {
    vector < char > rand_vector = generate_random_chars(count);
    for (size_t i = 0; i < rand_vector.size(); ++i) {
      fout << rand_vector[i] << " ";
      if (i < 500) {
        ui -> plainTextEdit -> moveCursor(QTextCursor::End);
        ui -> plainTextEdit -> insertPlainText(QChar(rand_vector[i]));
        ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" "));
      }
      if (i == 500) {
        ui -> plainTextEdit -> moveCursor(QTextCursor::End);
        ui -> plainTextEdit -> insertPlainText(QString::fromStdString(" ....."));
      }
    }
  }
}

void MainWindow::clear() {
  ui -> plainTextEdit -> clear();
  ui -> plainTextEdit -> setReadOnly(false);
  ofstream fout(DATAFILE);
  fout.clear();
}

void MainWindow::test() {
  ifstream fin(DATAFILE);
  string type = datatype -> currentText().toStdString();

  if (type == "integer") {
    TreeTesting < int > test;
    vector < int > data;
    int k;
    while (fin >> k) {
      data.push_back(k);
    }
    double time = 0;
    if (BinButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("BinTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("BinTree", "find", data);
      } else {
        time = test.check_time("BinTree", "erase", data);
      }
    }
    ui -> lcdNumber -> display(time);
    time = 0;
    if (CartButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("CartTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("CartTree", "find", data);
      } else {
        time = test.check_time("CartTree", "erase", data);
      }
    }
    ui -> lcdNumber_2 -> display(time);
    time = 0;
    if (AvlButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("AvlTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("AvlTree", "find", data);
      } else {
        time = test.check_time("AvlTree", "erase", data);
      }
    }
    ui -> lcdNumber_3 -> display(time);
    time = 0;
    if (RBButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("RBTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("RBTree", "find", data);
      } else {
        time = test.check_time("RBTree", "erase", data);
      }
    }
    ui -> lcdNumber_4 -> display(time);
  }

  if (type == "float") {
    TreeTesting < float > test;
    vector < float > data;
    float k;
    while (fin >> k) {
      data.push_back(k);
    }
    double time = 0;
    if (BinButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("BinTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("BinTree", "find", data);
      } else {
        time = test.check_time("BinTree", "erase", data);
      }
    }
    ui -> lcdNumber -> display(time);
    time = 0;
    if (CartButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("CartTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("CartTree", "find", data);
      } else {
        time = test.check_time("CartTree", "erase", data);
      }
    }
    ui -> lcdNumber_2 -> display(time);
    time = 0;
    if (AvlButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("AvlTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("AvlTree", "find", data);
      } else {
        time = test.check_time("AvlTree", "erase", data);
      }
    }
    ui -> lcdNumber_3 -> display(time);
    time = 0;
    if (RBButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("RBTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("RBTree", "find", data);
      } else {
        time = test.check_time("RBTree", "erase", data);
      }
    }
    ui -> lcdNumber_4 -> display(time);
  }

  if (type == "char") {
    TreeTesting < char > test;
    vector < char > data;
    char k;
    while (fin >> k) {
      data.push_back(k);
    }
    double time = 0;
    if (BinButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("BinTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("BinTree", "find", data);
      } else {
        time = test.check_time("BinTree", "erase", data);
      }
    }
    ui -> lcdNumber -> display(time);
    time = 0;
    if (CartButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("CartTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("CartTree", "find", data);
      } else {
        time = test.check_time("CartTree", "erase", data);
      }
    }
    ui -> lcdNumber_2 -> display(time);
    time = 0;
    if (AvlButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("AvlTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("AvlTree", "find", data);
      } else {
        time = test.check_time("AvlTree", "erase", data);
      }
    }
    ui -> lcdNumber_3 -> display(time);
    time = 0;
    if (RBButtonPressed) {
      if (functype -> currentText().toStdString() == "insert") {
        time = test.check_time("RBTree", "insert", data);
      } else if (functype -> currentText().toStdString() == "find") {
        time = test.check_time("RBTree", "find", data);
      } else {
        time = test.check_time("RBTree", "erase", data);
      }
    }
    ui -> lcdNumber_4 -> display(time);
  }
}
