/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <WCDB/column_index.hpp>
#include <WCDB/expression.hpp>
#include <WCDB/statement_create_index.hpp>
#include <WCDB/utility.hpp>

namespace WCDB {

StatementCreateIndex &StatementCreateIndex::create(const std::string &index,
                                                   bool unique,
                                                   bool ifNotExists)
{
    m_description.append("CREATE ");
    if (unique) {
        m_description.append("UNIQUE ");
    }
    m_description.append("INDEX ");
    if (ifNotExists) {
        m_description.append("IF NOT EXISTS ");
    }
    m_description.append(index);
    return *this;
}

StatementCreateIndex &
StatementCreateIndex::on(const std::string &table,
                         const std::list<const ColumnIndex> &indexList)
{
    m_description.append(" ON " + table + "(" + stringByJoiningList(indexList) +
                         ")");
    return *this;
}

StatementCreateIndex &StatementCreateIndex::on(const std::string &table,
                                               const ColumnIndex &index)
{
    m_description.append(" ON " + table + "(" + index.getDescription() + ")");
    return *this;
}

StatementCreateIndex &StatementCreateIndex::where(const Expression &expression)
{
    if (!expression.isEmpty()) {
        m_description.append(" WHERE " + expression.getDescription());
    }
    return *this;
}

Statement::Type StatementCreateIndex::getStatementType() const
{
    return Statement::Type::CreateIndex;
}

} //namespace WCDB
