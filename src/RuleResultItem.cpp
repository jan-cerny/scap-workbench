/*
 * Copyright 2015 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Martin Preisler <mpreisle@redhat.com>
 */

#include "RuleResultItem.h"
#include "APIHelpers.h"

RuleResultItem::RuleResultItem(struct xccdf_rule* rule, struct xccdf_policy* policy, QWidget* parent):
    QWidget(parent)
{
    mUi.setupUi(this);
    mUi.description->hide();

    mUi.title->setText(oscapItemGetReadableTitle(xccdf_rule_to_item(rule), policy));
    mDescriptionHTML = oscapItemGetReadableDescription(xccdf_rule_to_item(rule), policy);

    QObject::connect(
        mUi.showDescriptionCheckBox, SIGNAL(toggled(bool)),
        this, SLOT(showDescriptionToggled(bool))
    );
}

RuleResultItem::~RuleResultItem()
{}

void RuleResultItem::setRuleResult(const QString& result)
{
    QString resultStyleSheet = "text-align: center; font-weight: bold; color: #ffffff; padding: 3px; ";
    QString resultTooltip;

    if (result.isEmpty())
    {
        resultTooltip = "";
    }
    else if (result == "processing")
    {
        resultStyleSheet += "background: #808080; ";
        resultTooltip = QObject::tr("This rule is currently being processed.");
    }
    else if (result == "pass")
    {
        resultStyleSheet += "background: #5cb85c; ";
        resultTooltip = QObject::tr("The target system or system component satisfied all the conditions of this rule.");
    }
    else if (result == "fail")
    {
        resultStyleSheet += "background: #d9534f; ";
        resultTooltip = QObject::tr("The target system or system component did not satisfy every condition of this rule.");
    }
    else if (result == "error")
    {
        resultStyleSheet += "background: #d9534f; ";
        resultTooltip = QObject::tr("The checking engine could not complete the evaluation, therefore the status of the target's "
                "compliance with the rule is not certain. This could happen, for example, if a testing "
                "tool was run with insufficient privileges and could not gather all of the necessary information.");
    }
    else if (result == "unknown")
    {
        resultStyleSheet += "background: #f0ad4e; ";
        resultTooltip = QObject::tr("The testing tool encountered some problem and the result is unknown.");
    }
    else if (result == "notapplicable")
    {
        resultStyleSheet += "background: #808080; ";
        resultTooltip = QObject::tr("The rule was not applicable to the target machine of the test. For example, the "
                "rule might have been specific to a different version of the target OS, or it might "
                "have been a test against a platform feature that was not installed.");
    }
    else if (result == "notchecked")
    {
        resultStyleSheet += "background: #808080; ";
        resultTooltip = QObject::tr("The rule was not evaluated by the checking engine. There were no check elements "
                "inside the rule or none of the check systems of the check elements were supported.");
    }
    else if (result == "notselected")
    {
        resultStyleSheet += "background: #808080; ";
        resultTooltip = QObject::tr("The rule was not selected in the benchmark.");
    }
    else if (result == "informational")
    {
        resultStyleSheet += "background: #808080; ";
        resultTooltip = QObject::tr("The rule was checked, but the output from the checking engine is simply "
                "information for auditors or administrators; it is not a compliance category.");
    }
    else if (result == "fixed")
    {
        resultStyleSheet += "background: #5cb85c; ";
        resultTooltip = QObject::tr("The rule had failed, but was then fixed (most probably using remediation).");
    }
    else
    {
        // TODO: signal error?
    }

    mUi.result->setText(result);
    mUi.result->setStyleSheet(resultStyleSheet);
    mUi.result->setToolTip(resultTooltip);

    // Highlight currently processed rule
    if (result == "processing")
        mUi.title->setStyleSheet("background: #808080");
    else
        mUi.title->setStyleSheet("");
}

bool RuleResultItem::hasRuleResult() const
{
    return !mUi.result->text().isEmpty() && mUi.result->text() != "processing";
}

void RuleResultItem::showDescriptionToggled(bool checked)
{
    if (checked && mUi.description->text().isEmpty())
        mUi.description->setText(mDescriptionHTML);

    mUi.description->setVisible(checked);
}
