#ifndef RULES_MODEL_H
#define RULES_MODEL_H

#include <QAbstractListModel>
#include "core/file_mover.hpp"

class RulesModel: public QAbstractListModel
{
  Q_OBJECT
public:
  enum RuleRoles
  {
    TypeRole = Qt::UserRole + 1,
    TargetDirRole,
    ExtensionsRole,
    DurationRole,
    NameRole,
    IsGreaterThanDurationRole,
    IsCheckRegisterRole,
    ExceptionsRole
  };

  explicit RulesModel(FileMover& fileMover, QObject* parent = nullptr);

  Q_INVOKABLE void loadRulesForDir(const QString& dirName);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

private:
  FileMover& fileMover_;
  std::vector<details::FileRule> rules_;
};

#endif // RULES_MODEL_H
