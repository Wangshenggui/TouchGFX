#include <gui/common/ScrollingWheels/SparseContainerList.hpp>

SparseContainerList::SparseContainerList()
{
}

void SparseContainerList::setup(bool isHorizontal_, bool isCircular_,
                                int16_t widgetWidth, int16_t widgetHeight, int16_t selectedItemOffset_, int16_t containerSize, int16_t containerSpacing,
                                int16_t numItems_, int16_t numContainers_, GenericCallback<int, Container**>& getElementCallback, GenericCallback<int, int>& callback_)
{
    isHorizontal = isHorizontal_;
    isCircular = isCircular_;
    callback = &callback_;

    setWidth(widgetWidth);
    setHeight(widgetHeight);

    selectedItemOffset = selectedItemOffset_;
    itemSize = containerSize + containerSpacing;
    assert(itemSize > 0);
    spacing = containerSpacing;

    numItems = numItems_;

    // Calculate number of required containers. Worst case is one pixel visible of container at top and rest stacked tightly
    int16_t requiredContainers = 1 + (((isHorizontal ? widgetWidth : widgetHeight) - 1) + (itemSize - 1)) / itemSize;
    if (!isCircular)
    {
        // We never require more containers than the number of elements
        if (requiredContainers > numItems)
        {
            requiredContainers = numItems;
        }
    }
    assert(numContainers_ >= requiredContainers);
    //    assert(numContainers_ <= numItems);

    // Copy Parameters
    numContainers = numContainers_;
    getElement = &getElementCallback;

    Container* container;
    // Remove everything
    Container::removeAll();
    // Add the itemContainers
    for (int i = 0; i < numContainers; i++)
    {
        getElement->execute(i, &container);
        // Setup the wildcard and type text for each of the text areas
        //itemContainerTextAreas[i].setWildcard(textAreaWildcardBuffers);
        //itemContainerTextAreas[i].setTypedText(TypedText(placeholderTextId));
        // Resize the containers
        if (isHorizontal)
        {
            container->setPosition(0, 0, containerSize, getHeight());
        }
        else
        {
            container->setPosition(0, 0, getWidth(), containerSize);
        }
        // Add each container for later positioning
        Container::add(*container);
    }

    allContainersInitialized = false;
    firstItem = 0;
    firstContainer = 0;
    setVirtualOffset(0);
}

void SparseContainerList::setVirtualOffset(int32_t virtualOffset)
{
    // virtualY is the Y location of item[0] relative to the center element
    // 0 => item[0] is perfectly selected, -itemHeight => item[1] is perfectly selected, itemHeight => item[N-1] is perfectly selected etc.
    // One item will start at VirualY, find position of first widget in container
    int32_t firstContainerOffset = virtualOffset + selectedItemOffset; // Relative to top of widget
    int16_t newFirstItem = 0;
    if (firstContainerOffset > 0)
    {
        int numItems = firstContainerOffset / itemSize + 1;
        newFirstItem -= numItems;
        firstContainerOffset -= numItems * itemSize;
    }
    if (firstContainerOffset <= -itemSize)
    {
        int numItems = firstContainerOffset / itemSize;
        newFirstItem -= numItems;
        firstContainerOffset -= numItems * itemSize;
    }
    if (isCircular)
    {
        // Make sure that firstIndex is "in range"
        newFirstItem %= numItems;
        newFirstItem = (newFirstItem + numItems) % numItems;
    }
    else
    {
        if (newFirstItem < 0)
        {
            firstContainerOffset -= newFirstItem * itemSize;
            newFirstItem = 0;
        }
        else if (newFirstItem + numContainers > numItems)
        {
            int x = numItems - (newFirstItem + numContainers);
            firstContainerOffset += x * itemSize;
            newFirstItem += x;
        }
    }

    int containerDelta = 0;
    if (allContainersInitialized && firstItem != newFirstItem)
    {
        containerDelta = numContainers;
        for (int i = 1; i < numContainers; i++)
        {
            int fi = (firstItem + i);
            int nfi = (newFirstItem + i);
            if (isCircular)
            {
                fi %= numItems;
                nfi %= numItems;
            }
            if (fi == newFirstItem)
            {
                containerDelta = -i;
                break;
            }
            if (nfi == firstItem)
            {
                containerDelta = i;
                break;
            }
        }
    }
    firstContainer = ((firstContainer - containerDelta) + numContainers) % numContainers;
    firstItem = newFirstItem;

    Container* container;
    for (int i = 0; i < numContainers; i++)
    {
        int containerIndex = (firstContainer + i) % numContainers;
        getElement->execute(containerIndex, &container);
        if (isHorizontal)
        {
            container->setX(firstContainerOffset + i * itemSize + spacing / 2);
        }
        else
        {
            container->setY(firstContainerOffset + i * itemSize + spacing / 2);
        }

        int index = i + firstItem;
        if (isCircular)
        {
            index %= numItems;
        }
        else
        {
            if (index < 0 || index >= numItems)
            {
                index = -1;
            }
        }
        if (index < 0)
        {
            container->setVisible(false);
        }
        else
        {
            container->setVisible(true);
            // Only fill if first time or outside old range
            if (!allContainersInitialized || (i < containerDelta || i >= numContainers + containerDelta))
            {
                if (callback->isValid())
                {
                    callback->execute(containerIndex, index);
                }
            }
        }
    }
    allContainersInitialized = true;
}

int16_t SparseContainerList::getItemIndex(int16_t containerIndex)
{
    if (containerIndex < 0 || containerIndex >= numContainers)
    {
        return -1;
    }
    int16_t itemNumber = ((containerIndex + numContainers - firstContainer) % numContainers) + firstItem;
    if (isCircular)
    {
        itemNumber %= numItems;
    }
    if (itemNumber < 0 || itemNumber >= numItems)
    {
        return -1;
    }
    return itemNumber;
}

int16_t SparseContainerList::getContainerIndices(int16_t itemIndex, int16_t* containerIndex, int16_t num)
{
    int16_t numFound = 0;
    for (int16_t i = 0; i < numContainers; i++)
    {
        int16_t cIndex = firstContainer + i;
        int16_t index = firstItem + i;
        if (isCircular)
        {
            index %= numItems;
        }
        if (index == itemIndex)
        {
            if (numFound < num)
            {
                containerIndex[numFound] = cIndex;
                numFound++;
            }
            else
            {
                break;
            }
        }
    }
    return numFound;
}

int16_t SparseContainerList::getContainerIndex(int16_t itemIndex, int16_t prevContainerIndex /*= -1*/)
{
    if (prevContainerIndex >= -1 || prevContainerIndex < numContainers)
    {
        if (prevContainerIndex > -1)
        {
            prevContainerIndex = (prevContainerIndex - firstContainer + numContainers) % numContainers;
        }
        for (int16_t i = prevContainerIndex + 1; i < numContainers; i++)
        {
            int16_t index = firstItem + i;
            if (isCircular)
            {
                index %= numItems;
            }
            if (index == itemIndex)
            {
                return (firstContainer + i) % numContainers;
            }
        }
    }
    return -1;
}
