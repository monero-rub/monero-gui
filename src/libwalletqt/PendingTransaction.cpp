#include "PendingTransaction.h"
#include "xmc_int_to_double.hpp"

PendingTransaction::Status PendingTransaction::status() const
{
    return static_cast<Status>(m_pimpl->status());
}

QString PendingTransaction::errorString() const
{
    return QString::fromStdString(m_pimpl->errorString());
}

bool PendingTransaction::commit()
{
    // Save transaction to file if fileName is set.
    if(!m_fileName.isEmpty())
        return m_pimpl->commit(m_fileName.toStdString());
    return m_pimpl->commit(m_fileName.toStdString());
}

double PendingTransaction::amount() const
{
    return xmc_int_to_double(m_pimpl->amount());
}

double PendingTransaction::dust() const
{
    return xmc_int_to_double(m_pimpl->dust());
}

double PendingTransaction::fee() const
{
    return xmc_int_to_double(m_pimpl->fee());
}


QStringList PendingTransaction::txid() const
{
    QStringList list;
    std::vector<std::string> txid = m_pimpl->txid();
    for (const auto &t: txid)
        list.append(QString::fromStdString(t));
    return list;
}


quint64 PendingTransaction::txCount() const
{
    return m_pimpl->txCount();
}

QList<QVariant> PendingTransaction::subaddrIndices() const
{
    std::vector<std::set<uint32_t>> subaddrIndices = m_pimpl->subaddrIndices();
    QList<QVariant> result;
    for (const auto& x : subaddrIndices)
        for (uint32_t i : x)
            result.push_back(i);
    return result;
}

void PendingTransaction::setFilename(const QString &fileName)
{
    m_fileName = fileName;
}

PendingTransaction::PendingTransaction(Monero::PendingTransaction *pt, QObject *parent)
    : QObject(parent), m_pimpl(pt)
{

}
