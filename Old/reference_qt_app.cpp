#include <QApplication>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedLayout>
#include <QToolButton>
#include <QWidget>

#include <QString>

namespace {

QWidget* createDetatchedUiWindow() {
  auto* window = new QWidget(nullptr);
  window->setWindowTitle("peanut butter (detached)");
  window->setMinimumSize(570, 572);

  auto* layout = new QGridLayout(window);
  layout->setContentsMargins(12, 12, 12, 12);
  layout->setSpacing(8);

  for (int c = 0; c < 8; ++c) {
    layout->setColumnStretch(c, c == 7 ? 0 : 1);
  }

  auto* source_edit = new QLineEdit(window);
  auto* archive_edit = new QLineEdit(window);
  auto* unarchive_edit = new QLineEdit(window);
  auto* recovery_edit = new QLineEdit(window);
  auto* archive_size_combo = new QComboBox(window);
  auto* clear_logs_button = new QPushButton("Clear Logs", window);
  auto* source_clear_button = new QToolButton(window);
  auto* source_pick_button = new QToolButton(window);
  auto* archive_clear_button = new QToolButton(window);
  auto* archive_pick_button = new QToolButton(window);
  auto* unarchive_clear_button = new QToolButton(window);
  auto* unarchive_pick_button = new QToolButton(window);
  auto* recovery_clear_button = new QToolButton(window);
  auto* recovery_pick_button = new QToolButton(window);
  auto* pack_button = new QPushButton("Bundle", window);
  auto* unpack_button = new QPushButton("Unbundle", window);
  auto* sanity_button = new QPushButton("Sanity", window);
  auto* recover_button = new QPushButton("Recover", window);
  auto* action_spinner = new QProgressBar(window);
  auto* action_row_host = new QWidget(window);
  auto* action_buttons_row = new QWidget(action_row_host);
  auto* action_spinner_row = new QWidget(action_row_host);
  auto* action_row_stack = new QStackedLayout(action_row_host);
  auto* action_buttons_layout = new QHBoxLayout(action_buttons_row);
  auto* action_spinner_layout = new QHBoxLayout(action_spinner_row);
  auto* debug_console = new QPlainTextEdit(window);

  source_edit->setPlaceholderText("pack source folder -> archive folder");
  archive_edit->setPlaceholderText("archive folder -> unarchive folder");
  unarchive_edit->setPlaceholderText("unarchive folder");
  recovery_edit->setPlaceholderText("recovery start file");

  source_clear_button->setText("X");
  archive_clear_button->setText("X");
  unarchive_clear_button->setText("X");
  recovery_clear_button->setText("X");
  source_pick_button->setText("Folder...");
  archive_pick_button->setText("Folder...");
  unarchive_pick_button->setText("Folder...");
  recovery_pick_button->setText("File...");

  constexpr int kInputHeight = 44;
  constexpr int kActionHeight = 54;
  for (QLineEdit* edit : {source_edit, archive_edit, unarchive_edit, recovery_edit}) {
    edit->setFixedHeight(kInputHeight);
  }
  clear_logs_button->setFixedHeight(kInputHeight);
  archive_size_combo->setFixedHeight(kInputHeight);
  for (QToolButton* btn : {source_clear_button, archive_clear_button, unarchive_clear_button, recovery_clear_button}) {
    btn->setFixedSize(54, kInputHeight);
  }
  for (QToolButton* btn : {source_pick_button, archive_pick_button, unarchive_pick_button, recovery_pick_button}) {
    btn->setFixedSize(72, kInputHeight);
  }

  for (QPushButton* button : {pack_button, unpack_button, sanity_button, recover_button}) {
    button->setFixedHeight(kActionHeight);
    button->setMinimumHeight(kActionHeight);
    button->setMaximumHeight(kActionHeight);
  }

  action_spinner->setRange(0, 0);
  action_spinner->setTextVisible(false);
  action_spinner->setFixedHeight(kActionHeight);

  action_buttons_layout->setContentsMargins(0, 0, 0, 0);
  action_buttons_layout->setSpacing(8);
  action_buttons_layout->addWidget(pack_button, 1);
  action_buttons_layout->addWidget(unpack_button, 1);
  action_buttons_layout->addWidget(sanity_button, 1);
  action_buttons_layout->addWidget(recover_button, 1);

  action_spinner_layout->setContentsMargins(0, 0, 0, 0);
  action_spinner_layout->addWidget(action_spinner, 1);
  action_row_stack->setContentsMargins(0, 0, 0, 0);
  action_row_stack->addWidget(action_buttons_row);
  action_row_stack->addWidget(action_spinner_row);
  action_row_stack->setCurrentWidget(action_buttons_row);

  layout->addWidget(source_clear_button, 0, 0);
  layout->addWidget(source_edit, 0, 1, 1, 6);
  layout->addWidget(source_pick_button, 0, 7);
  layout->addWidget(archive_clear_button, 1, 0);
  layout->addWidget(archive_edit, 1, 1, 1, 6);
  layout->addWidget(archive_pick_button, 1, 7);
  layout->addWidget(unarchive_clear_button, 2, 0);
  layout->addWidget(unarchive_edit, 2, 1, 1, 6);
  layout->addWidget(unarchive_pick_button, 2, 7);
  layout->addWidget(recovery_clear_button, 3, 0);
  layout->addWidget(recovery_edit, 3, 1, 1, 6);
  layout->addWidget(recovery_pick_button, 3, 7);
  layout->addWidget(archive_size_combo, 8, 0, 1, 4);
  layout->addWidget(clear_logs_button, 8, 4, 1, 4);
  layout->addWidget(action_row_host, 10, 0, 1, 8);
  layout->addWidget(debug_console, 12, 0, 1, 8);
  layout->setRowStretch(12, 1);

  auto onActionClicked = [&](const QString& action) {
    if (action.isEmpty()) {
      QMessageBox::warning(window, QLatin1String("Invalid Action"), QLatin1String("No action selected."));
      return;
    }
    debug_console->appendPlainText(QString::fromLatin1("Started: %1").arg(action));
  };
  QObject::connect(pack_button, &QPushButton::clicked, window, [=]() { onActionClicked("Bundle"); });
  QObject::connect(unpack_button, &QPushButton::clicked, window, [=]() { onActionClicked("Unbundle"); });
  QObject::connect(sanity_button, &QPushButton::clicked, window, [=]() { onActionClicked("Sanity"); });
  QObject::connect(recover_button, &QPushButton::clicked, window, [=]() { onActionClicked("Recover"); });

  window->setLayout(layout);
  return window;
}

}  // namespace

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QWidget* detached_window = createDetatchedUiWindow();
  detached_window->show();
  return app.exec();
}
