#ifndef SPARSECONTAINERLIST_HPP
#define SPARSECONTAINERLIST_HPP

#include <touchgfx/containers/Container.hpp>

using namespace touchgfx;

/**
* @class SparseContainerItems SparseContainerList.hpp touchgfx/containers/SparseContainerList.hpp
*
 * @brief A sparse container List item.
 *
 *        A sparse container List item. Basically just a helper to automatically setup the
 *        callback function to get a specific element from the list of custom containers.
 *
 * @tparam T The custom Container class.
 * @tparam S The number of Container items.
 */
template <class T, int S> class SparseContainerItems
{
public:

    /**
     * @fn SparseContainerItems::SparseContainerItems() : getElementCallback(this, &SparseContainerItems::getElement)
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    SparseContainerItems() : getElementCallback(this, &SparseContainerItems::getElement) {}

    /**
     * @fn virtual SparseContainerItems::~SparseContainerItems()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~SparseContainerItems() {}

    /**
     * @fn void SparseContainerItems::getElement(int containerIndex, Container** container)
     *
     * @brief Gets an element.
     *
     *        Gets an element.
     *
     * @param containerIndex     Zero-based index of the container.
     * @param [in,out] container If non-null, the container.
     */
    void getElement(int containerIndex, Container** container)
    {
        assert(containerIndex >= 0 && containerIndex < S);
        *container = &element[containerIndex];
    }
    T element[S];   ///< The elements
    Callback<SparseContainerItems, int, Container**> getElementCallback;    ///< Callback to get a given element
};

class SparseContainerList : public Container
{
public:

    /**
     * @fn SparseContainerList::SparseContainerList();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    SparseContainerList();

    /**
     * @fn void SparseContainerList::setup(bool isHorizontal_, bool isCircular_, int16_t widgetWidth, int16_t widgetHeight, int16_t selectedItemOffset_, int16_t containerSize, int16_t containerSpacing, int16_t numItems_, int16_t numContainers_, Container* containers_, GenericCallback<int, int>& callback_);
     *
     * @brief Setups a sparse vertical container list.
     *
     *        Setups a sparse vertical container list. The special thing is that there are (a
     *        lot) fewer containers than values to scroll through. This save resources, but
     *        requires a little extra work when the list is scrolled.
     *
     * @param isHorizontal_       true if the containers are arranged side by side, false if the
     *                            containers are above and below each other.
     * @param isCircular_         true for circular (infinite) scrolling. Often true for Hours and
     *                            minutes selection, false for AM/PM selectors.
     * @param widgetWidth         Width of the widget.
     * @param widgetHeight        Height of the widget.
     * @param selectedItemOffset_ The y coordinate of the selected item on the screen.
     * @param containerSize       Size of each item in the list.
     * @param containerSpacing    The container spacing. If the number is negative it will be the
     *                            container overlap.
     * @param numItems_           Number of items. Typically higher than numItemContainers_.
     * @param numContainers_      Number of item containers simultaneously on the screen. Each of
     *                            these must contain a text area already positioned, colored,
     *                            etc.
     * @param [in] containers_    The numItemContainers_'s item containers. These are sized, placed
     *                            and possibly made non-visible automatically.
     * @param [in] callback_      The callback to invoke when a container needs to be updated with
     *                            new content.
     */
    void setup(bool isHorizontal_, bool isCircular_,
               int16_t widgetWidth, int16_t widgetHeight, int16_t selectedItemOffset_, int16_t containerSize, int16_t containerSpacing,
               int16_t numItems_, int16_t numContainers_, GenericCallback<int, Container**>& getElementCallback, GenericCallback<int, int>& callback_);

    /**
     * @fn void SparseContainerList::setVirtualOffset(int16_t virtualOffset);
     *
     * @brief Sets virtual coordinate.
     *
     *        Sets virtual coordinate. Does not move to the given coordinate, but places the
     *        item containers and fill correct content into the containers to give the
     *        impression that everything has been scrolled to the given coordinate.
     *
     *        A value of 0 means that item 0 is in the "selected" spot on the screen. "-
     *        itemHeight" selects item 1, etc.
     *
     *        Care is taken to not fill too often.
     *
     * @param virtualOffset The virtual coordinate.
     */
    void setVirtualOffset(int32_t virtualOffset);

    int16_t getItemIndex(int16_t containerIndex);

    /**
     * @fn int16_t SparseContainerList::getContainerIndices(int16_t itemIndex, int16_t* containerIndex, int16_t num);
     *
     * @brief Gets container indices.
     *
     *        Gets container indices. Only useful when the number of items is smaller than the
     *        number of containers as the same item might be in more than one container on the
     *        screen. The passed array will be filled with the container indices and the number
     *        of indices found is returned.
     *
     * @param itemIndex            Zero-based index of the item.
     * @param [out] containerIndex Array where the container indices are stored.
     * @param num                  Size of containerIndex array.
     *
     * @return The number of container indices found.
     *
     * @see getFirstContainerIndex
     */
    int16_t getContainerIndices(int16_t itemIndex, int16_t* containerIndex, int16_t num);

    /**
     * @fn int16_t SparseContainerList::getContainerIndex(int16_t itemIndex, int16_t prevContainerIndex = -1);
     *
     * @brief Gets the container index of an item.
     *
     *        Gets the container index of an item. If the number of items is smaller than the
     *        number of containers, the same item can be in more than one container. In that
     *        case, calling this function again with the previously returned index as second
     *        parameter, the index of the next container containing the item will be returned.
     *
     * @param itemIndex          Index of the item.
     * @param prevContainerIndex Index of the previous container. If given, search starts after
     *                           this index.
     *
     * @return The first container index with the given item. Returns -1 if the item is not in a
     *         container.
     *
     * @see getContainerIndices
     */
    int16_t getContainerIndex(int16_t itemIndex, int16_t prevContainerIndex = -1);

    /**
     * @fn int16_t SparseContainerList::getNumItemContainers() const
     *
     * @brief Gets number of item containers.
     *
     *        Gets number of item containers.
     *
     * @return The number of item containers.
     */
    int16_t getNumItemContainers() const
    {
        return numContainers;
    }

    /**
     * @fn int16_t SparseContainerList::getNumItems() const
     *
     * @brief Gets number of items.
     *
     *        Gets number of items.
     *
     * @return The number of items.
     */
    int16_t getNumItems() const
    {
        return numItems;
    }

private:
    int16_t selectedItemOffset;
    int16_t itemSize;
    int16_t spacing;

    int16_t numItems;
    int16_t numContainers;
    GenericCallback<int, Container**>* getElement;

    int16_t firstItem;
    int16_t firstContainer;

    GenericCallback<int, int>* callback;
    bool isCircular;
    bool isHorizontal;
    bool allContainersInitialized;
};

#endif // SPARSECONTAINERLIST_HPP
