#include "stdafx.h"
#include "AdjustableThumbnail.h"

AdjustableThumbnail::AdjustableThumbnail(void) :
	thumbnail()
{
}

AdjustableThumbnail::~AdjustableThumbnail(void)
{
	UnsetThumbnail();
}

bool AdjustableThumbnail::SetThumbnail(HWND const & target, HWND const & source)
{
	// Check
	if (target == NULL) return false;
	if (source == NULL) return false;

	// Register thumbnail
	bool success = thumbnail.Register(target, source);

	// Resize
	if (success)
	{
		RECT sourceRect;
		GetClientRect(source, &sourceRect);
		sourceRect.right -= sourceRect.left;
		sourceRect.bottom -= sourceRect.top;
		sourceRect.left = 0;
		sourceRect.top = 0;
		success = thumbnail.Scale(sourceRect);
	}

	// Done
	return success;
}

bool AdjustableThumbnail::UnsetThumbnail()
{
	return thumbnail.Unregister();
}

bool AdjustableThumbnail::SetSize(RECT const & rect)
{
	return thumbnail.Scale(rect);
}
