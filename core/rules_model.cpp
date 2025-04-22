#include "rules_model.h"

RulesModel::RulesModel(FileMover& fileMover, QObject* parent):
  fileMover_(fileMover)
{}

int RulesModel::rowCount(const QModelIndex& parent) const
{
  return parent.isValid() ? 0 : rules_.size();
}

QVariant RulesModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || index.row() >= rules_.size())
  {
    return QVariant();
  }

  const auto& rule = rules_[index.row()];

  return std::visit([role](auto&& arg) -> QVariant
      {
        using T = std::decay_t< decltype(arg) >;
        if constexpr (std::is_same_v< T, details::MovingByExtRule >)
        {
          switch (role)
          {
          case TypeRole:
            return "MovingByExt";
          case TargetDirRole:
            return QString::fromStdString(arg.targetDir.string());
          case ExtensionsRole:
          {
            QStringList exts;
            for (const auto& ext: arg.ext)
            {
              exts << QString::fromStdString(ext.string());
            }
            return exts;
          }
          case ExceptionsRole:
          {
            QStringList exceptions;
            for (const auto& exception: arg.exceptions)
            {
              exceptions << QString::fromStdString(exception.string());
            }
            return exceptions;
          }
          default:
            return QVariant();
          }
        }
        else if constexpr (std::is_same_v< T, details::MovingByDateRule >)
        {
          switch (role)
          {
          case TypeRole:
            return "MovingByDate";
          case TargetDirRole:
            return QString::fromStdString(arg.targetDir.string());
          case DurationRole:
            return arg.duration.count();
          case IsGreaterThanDurationRole:
            return arg.isGreaterThanDuration;
          case ExceptionsRole:
          {
            QStringList exceptions;
            for (const auto& exception: arg.exceptions)
            {
              exceptions << QString::fromStdString(exception.string());
            }
            return exceptions;
          }
          default:
            return QVariant();
          }
        }
        else if constexpr (std::is_same_v< T, details::MovingByNameRule >)
        {
          switch (role)
          {
          case TypeRole:
            return "MovingByName";
          case TargetDirRole:
            return QString::fromStdString(arg.targetDir.string());
          case NameRole:
            return QString::fromStdString(arg.name);
          case IsCheckRegisterRole:
            return arg.isCheckRegister;
          case ExceptionsRole:
          {
            QStringList exceptions;
            for (const auto& exception: arg.exceptions)
            {
              exceptions << QString::fromStdString(exception.string());
            }
            return exceptions;
          }
          default:
            return QVariant();
          }
        }
        else if constexpr (std::is_same_v< T, details::MovingAllRule >)
        {
          switch (role)
          {
          case TypeRole:
            return "MovingAll";
          case TargetDirRole:
            return QString::fromStdString(arg.targetDir.string());
          case ExceptionsRole:
          {
            QStringList exceptions;
            for (const auto& exception: arg.exceptions)
            {
              exceptions << QString::fromStdString(exception.string());
          }
          return exceptions;
          }
          default:
            return QVariant();
          }
        }
        else if constexpr (std::is_same_v< T, details::DeletingByExtRule >)
        {
          switch (role)
          {
          case TypeRole:
            return "DeletingByExt";
          case ExtensionsRole:
          {
            QStringList exts;
            for (const auto& ext: arg.ext)
            {
              exts << QString::fromStdString(ext.string());
            }
            return exts;
          }
          case ExceptionsRole:
          {
            QStringList exceptions;
            for (const auto& exception: arg.exceptions)
            {
              exceptions << QString::fromStdString(exception.string());
            }
            return exceptions;
          }
          default:
            return QVariant();
          }
        }
        else if constexpr (std::is_same_v< T, details::DeletingByDateRule >)
        {
          switch (role)
          {
          case TypeRole:
            return "DeletingByDate";
          case DurationRole:
            return arg.duration.count();
          case IsGreaterThanDurationRole:
            return arg.isGreaterThanDuration;
          case ExceptionsRole:
          {
            QStringList exceptions;
            for (const auto& exception: arg.exceptions)
            {
            exceptions << QString::fromStdString(exception.string());
            }
            return exceptions;
          }
          default:
            return QVariant();
          }
        }
      }, rule);
}

QHash<int, QByteArray> RulesModel::roleNames() const
{
  return
  {
    { TypeRole, "type" },
    { TargetDirRole, "targetDir" },
    { ExtensionsRole, "extensions" },
    { DurationRole, "duration" },
    { NameRole, "name" },
    { IsGreaterThanDurationRole, "isGreaterThanDuration" },
    { IsCheckRegisterRole, "isCheckRegister" },
    { ExceptionsRole, "exceptions" }
  };
}

void RulesModel::loadRulesForDir(const QString& dirName)
{
  beginResetModel();
  try {
    rules_ = fileMover_.dirs_.at(dirName.toStdString()).getRules();
  }
  catch (const std::exception& e)
  {
    rules_.clear();
    qDebug() << e.what() << '\n';
  }
  endResetModel();
}
