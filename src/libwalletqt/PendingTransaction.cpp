#include "PendingTransaction.h"
#include "rub_int_to_double.hpp"

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
    /*
    rub_int rub_balance = m_pimpl->amount();
    std::cout<<"RUB_INT PendingTransaction BALANCE:" << rub_balance << std::endl;
    double d_balance = rub_int_to_double(rub_balance);
    std::cout<<"RUB Double PendingTransaction Balance:" << d_balance << std::endl;
    */
    return rub_int_to_double(m_pimpl->amount());
}

quint64 PendingTransaction::dust() const
{
    return m_pimpl->dust();
}

quint64 PendingTransaction::fee() const
{
    return m_pimpl->fee();
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
