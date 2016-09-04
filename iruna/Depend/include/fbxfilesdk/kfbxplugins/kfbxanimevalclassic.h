/*!  \file kfbxanimevalclassic.h
 */

#ifndef FBXFILESDK_KFBXPLUGINS_KFBXEVALUATIONCLASSIC_H
#define FBXFILESDK_KFBXPLUGINS_KFBXEVALUATIONCLASSIC_H

/**************************************************************************************

 Copyright (C) 2001 - 2010 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.

 The coded instructions, statements, computer programs, and/or related material 
 (collectively the "Data") in these files contain unpublished information 
 proprietary to Autodesk, Inc. and/or its licensors, which is protected by 
 Canada and United States of America federal copyright law and by international 
 treaties. 
 
 The Data may not be disclosed or distributed to third parties, in whole or in
 part, without the prior written consent of Autodesk, Inc. ("Autodesk").

 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING
 BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE, 
 NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR USE. 
 WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT THE OPERATION
 OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE. 
 
 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES
 OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE DAMAGES OR OTHER
 SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
 OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND),
 HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF LIABILITY, WHETHER DERIVED
 FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO, NEGLIGENCE), OR OTHERWISE,
 ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
 WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS
 OR DAMAGE. 

**************************************************************************************/
#include <fbxfilesdk/kfbxplugins/kfbxobject.h>
#include <fbxfilesdk/kfbxplugins/kfbxanimevaluator.h>
#include <fbxfilesdk/kfbxplugins/kfbxanimlayer.h>

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

/** This class is an implementation of the classic FbxSdk animation evaluation.
  * \nosubgrouping
  */
class KFBX_DLL KFbxAnimEvalClassic : public KFbxAnimEvaluator
{
    KFBXOBJECT_DECLARE(KFbxAnimEvalClassic, KFbxAnimEvaluator);

public:

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//    Anything beyond these lines may not be documented accurately and is 
//     subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
	virtual void EvaluateNodeTransform(KFbxNodeEvalState* pResult, KFbxNode* pNode, KTime pTime, KFbxAnimStack* pStack, KFbxNode::EPivotSet pPivotSet, bool pApplyTarget);
    virtual void EvaluatePropertyValue(KFbxAnimCurveNode* pResult, KFbxProperty& pProperty, KTime pTime, KFbxAnimStack* pStack);

    virtual KFbxObject* Clone(KFbxObject* pContainer, KFbxObject::ECloneType pCloneType) const;

private:
    KFbxAnimEvalClassic(KFbxSdkManager& pManager, char const* pName);
	virtual void Destruct(bool pRecursive, bool pDependents);

	enum eFbxBlendType {eFbxBlendSimple, eFbxBlendRotation, eFbxBlendScaling, eFbxBlendTypeCount};

	void ComputeTRSLocal(KFbxNodeEvalState* pResult, KFbxNode* pNode, KTime pTime, KFbxAnimStack* pStack);
	void ComputeTRSGlobal(KFbxNodeEvalState* pResult, KFbxNode* pNode, KTime pTime, KFbxAnimStack* pStack, KFbxNode::EPivotSet pPivotSet, bool pApplyTarget);
	void ComputeTRSAnimationLayer(KFbxNodeEvalState* pResult, KFbxNode* pNode, KFbxVector4& pLT, KFbxVector4& pLR, KFbxVector4& pLS, KTime pTime, KFbxAnimLayer* pLayer, bool pBlend);
	void BlendPropertyEvalWithLayer(double* pResult, int pResultSize, KFbxProperty& pProperty, KFbxNodeEvalState* pEvalState, KTime pTime, KFbxAnimLayer* pLayer, eFbxBlendType pType);
	void BlendSimple(double* pResult, int pResultSize, double* pApply, int pApplySize, double pWeight, KFbxAnimLayer::EBlendMode pBlendMode);
	void BlendRotation(double* pResult, int pResultSize, double* pApply, int pApplySize, double pWeight, KFbxAnimLayer::EBlendMode pBlendMode, KFbxAnimLayer::ERotationAccumulationMode pRotAccuMode, int pRotationOrder);
	void BlendScaling(double* pResult, int pResultSize, double* pApply, int pApplySize, double pWeight, KFbxAnimLayer::EBlendMode pBlendMode, KFbxAnimLayer::EScaleAccumulationMode pScaleAccuMode);

	double* mPropertyValues;
	int		mPropertySize;

	double*	mCurveNodeEvalValues;
	int		mCurveNodeEvalSize;

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS 
};

#include <fbxfilesdk/fbxfilesdk_nsend.h>

#endif /* FBXFILESDK_KFBXPLUGINS_KFBXEVALUATIONCLASSIC_H */
