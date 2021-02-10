// Copyright 2018 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include "VulkanHandleMapping.h"
#include "VulkanDispatch.h"

#include <vulkan/vulkan.h>

#include <memory>

#include "cereal/common/goldfish_vk_private_defs.h"
#include "cereal/common/goldfish_vk_transform.h"

class VkDecoderSnapshot;

namespace android {
namespace base {
class BumpPool;
class Stream;
} // namespace android
} // namespace base

namespace goldfish_vk {


// Class for tracking host-side state. Currently we only care about
// tracking VkDeviceMemory to make it easier to pass the right data
// from mapped pointers to the guest, but this could get more stuff
// added to it if for instance, we want to only expose a certain set
// of physical device capabilities, or do snapshots.

// This class may be autogenerated in the future.
// Currently, it works by interfacing with VkDecoder calling on_<apicall>
// functions.
class VkDecoderGlobalState {
public:
    VkDecoderGlobalState();
    ~VkDecoderGlobalState();

    // There should only be one instance of VkDecoderGlobalState
    // per process
    static VkDecoderGlobalState* get();

    // Snapshot save/load
    bool snapshotsEnabled() const;

    // Whether to clean up VK instance.
    // bug 149997534
    bool vkCleanupEnabled() const;

    void save(android::base::Stream* stream);
    void load(android::base::Stream* stream);

    // Lock/unlock of global state to serve as a global lock
    void lock();
    void unlock();

    // Sets the current created handles for snapshot load
    // which will override the effect of any new_boxed_*** calls.
    // They are consumed in sequence.
    // Returns number of bytes of |buffer|
    // that have been consumed for this purpose.
    size_t setCreatedHandlesForSnapshotLoad(const unsigned char* buffer);
    void clearCreatedHandlesForSnapshotLoad();

    VkResult on_vkEnumerateInstanceVersion(
        android::base::BumpPool* pool,
        uint32_t* pApiVersion);

    // Fast way to get dispatch tables associated with a Vulkan object.
    // VkInstance
    // VkPhysicalDevice
    // VkDevice
    // VkQueue
    // VkCommandBuffer

    VkResult on_vkCreateInstance(
        android::base::BumpPool* pool,
        const VkInstanceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkInstance* pInstance);

    void on_vkDestroyInstance(
        android::base::BumpPool* pool,
        VkInstance instance,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkEnumeratePhysicalDevices(
        android::base::BumpPool* pool,
        VkInstance instance,
        uint32_t* physicalDeviceCount,
        VkPhysicalDevice* physicalDevices);

    // Override features
    void on_vkGetPhysicalDeviceFeatures(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceFeatures* pFeatures);
    void on_vkGetPhysicalDeviceFeatures2(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceFeatures2* pFeatures);
    void on_vkGetPhysicalDeviceFeatures2KHR(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceFeatures2* pFeatures);

    // Override image format properties
    VkResult on_vkGetPhysicalDeviceImageFormatProperties(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkFormat format,
        VkImageType type,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        VkImageCreateFlags flags,
        VkImageFormatProperties* pImageFormatProperties);
    VkResult on_vkGetPhysicalDeviceImageFormatProperties2(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
        VkImageFormatProperties2* pImageFormatProperties);
    VkResult on_vkGetPhysicalDeviceImageFormatProperties2KHR(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
        VkImageFormatProperties2* pImageFormatProperties);

    // Override format features
    void on_vkGetPhysicalDeviceFormatProperties(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkFormat format,
        VkFormatProperties* pFormatProperties);
    void on_vkGetPhysicalDeviceFormatProperties2(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkFormat format,
        VkFormatProperties2* pFormatProperties);
    void on_vkGetPhysicalDeviceFormatProperties2KHR(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkFormat format,
        VkFormatProperties2* pFormatProperties);

    // Override API version
    void on_vkGetPhysicalDeviceProperties(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceProperties* pProperties);
    void on_vkGetPhysicalDeviceProperties2(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceProperties2* pProperties);
    void on_vkGetPhysicalDeviceProperties2KHR(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceProperties2* pProperties);

    // Override memory types advertised from host
    //
    void on_vkGetPhysicalDeviceMemoryProperties(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceMemoryProperties* pMemoryProperties);
    void on_vkGetPhysicalDeviceMemoryProperties2(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceMemoryProperties2* pMemoryProperties);
    void on_vkGetPhysicalDeviceMemoryProperties2KHR(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceMemoryProperties2* pMemoryProperties);

    // Override supported device extension lists
    VkResult on_vkEnumerateDeviceExtensionProperties(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        const char* pLayerName,
        uint32_t* pPropertyCount,
        VkExtensionProperties* pProperties);

    VkResult on_vkCreateDevice(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        const VkDeviceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDevice* pDevice);

    void on_vkGetDeviceQueue(
        android::base::BumpPool* pool,
        VkDevice device,
        uint32_t queueFamilyIndex,
        uint32_t queueIndex,
        VkQueue* pQueue);

    void on_vkDestroyDevice(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkCreateBuffer(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkBufferCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkBuffer* pBuffer);

    void on_vkDestroyBuffer(
        android::base::BumpPool* pool,
        VkDevice device,
        VkBuffer buffer,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkBindBufferMemory(
        android::base::BumpPool* pool,
        VkDevice device,
        VkBuffer buffer,
        VkDeviceMemory memory,
        VkDeviceSize memoryOffset);
    VkResult on_vkBindBufferMemory2(
        android::base::BumpPool* pool,
        VkDevice device,
        uint32_t bindInfoCount,
        const VkBindBufferMemoryInfo* pBindInfos);
    VkResult on_vkBindBufferMemory2KHR(
        android::base::BumpPool* pool,
        VkDevice device,
        uint32_t bindInfoCount,
        const VkBindBufferMemoryInfo* pBindInfos);

    VkResult on_vkCreateImage(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkImageCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkImage* pImage);

    void on_vkDestroyImage(
        android::base::BumpPool* pool,
        VkDevice device,
        VkImage image,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkBindImageMemory(android::base::BumpPool* pool,
                                  VkDevice device,
                                  VkImage image,
                                  VkDeviceMemory memory,
                                  VkDeviceSize memoryOffset);

    VkResult on_vkCreateImageView(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkImageViewCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkImageView* pView);

    void on_vkDestroyImageView(
        android::base::BumpPool* pool,
        VkDevice device,
        VkImageView imageView,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkCreateSampler(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkSamplerCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkSampler* pSampler);

    void on_vkDestroySampler(
        android::base::BumpPool* pool,
        VkDevice device,
        VkSampler sampler,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkCreateDescriptorSetLayout(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDescriptorSetLayout* pSetLayout);

    void on_vkDestroyDescriptorSetLayout(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDescriptorSetLayout descriptorSetLayout,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkCreateDescriptorPool(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkDescriptorPoolCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDescriptorPool* pDescriptorPool);

    void on_vkDestroyDescriptorPool(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDescriptorPool descriptorPool,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkResetDescriptorPool(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDescriptorPool descriptorPool,
        VkDescriptorPoolResetFlags flags);

    VkResult on_vkAllocateDescriptorSets(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkDescriptorSetAllocateInfo* pAllocateInfo,
        VkDescriptorSet* pDescriptorSets);

    VkResult on_vkFreeDescriptorSets(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDescriptorPool descriptorPool,
        uint32_t descriptorSetCount,
        const VkDescriptorSet* pDescriptorSets);

    void on_vkUpdateDescriptorSets(
        android::base::BumpPool* pool,
        VkDevice device,
        uint32_t descriptorWriteCount,
        const VkWriteDescriptorSet* pDescriptorWrites,
        uint32_t descriptorCopyCount,
        const VkCopyDescriptorSet* pDescriptorCopies);

    void on_vkCmdCopyBufferToImage(
        android::base::BumpPool* pool,
        VkCommandBuffer commandBuffer,
        VkBuffer srcBuffer,
        VkImage dstImage,
        VkImageLayout dstImageLayout,
        uint32_t regionCount,
        const VkBufferImageCopy* pRegions);

    void on_vkCmdCopyImage(android::base::BumpPool* pool,
                           VkCommandBuffer commandBuffer,
                           VkImage srcImage,
                           VkImageLayout srcImageLayout,
                           VkImage dstImage,
                           VkImageLayout dstImageLayout,
                           uint32_t regionCount,
                           const VkImageCopy* pRegions);
    void on_vkCmdCopyImageToBuffer(android::base::BumpPool* pool,
                                   VkCommandBuffer commandBuffer,
                                   VkImage srcImage,
                                   VkImageLayout srcImageLayout,
                                   VkBuffer dstBuffer,
                                   uint32_t regionCount,
                                   const VkBufferImageCopy* pRegions);

    void on_vkGetImageMemoryRequirements(
            android::base::BumpPool* pool,
            VkDevice device,
            VkImage image,
            VkMemoryRequirements* pMemoryRequirements);

    void on_vkGetImageMemoryRequirements2(
            android::base::BumpPool* pool,
            VkDevice device,
            const VkImageMemoryRequirementsInfo2* pInfo,
            VkMemoryRequirements2* pMemoryRequirements);

    void on_vkGetImageMemoryRequirements2KHR(
            android::base::BumpPool* pool,
            VkDevice device,
            const VkImageMemoryRequirementsInfo2* pInfo,
            VkMemoryRequirements2* pMemoryRequirements);

    void on_vkCmdPipelineBarrier(
            android::base::BumpPool* pool,
            VkCommandBuffer commandBuffer,
            VkPipelineStageFlags srcStageMask,
            VkPipelineStageFlags dstStageMask,
            VkDependencyFlags dependencyFlags,
            uint32_t memoryBarrierCount,
            const VkMemoryBarrier* pMemoryBarriers,
            uint32_t bufferMemoryBarrierCount,
            const VkBufferMemoryBarrier* pBufferMemoryBarriers,
            uint32_t imageMemoryBarrierCount,
            const VkImageMemoryBarrier* pImageMemoryBarriers);

    // Do we need to wrap vk(Create|Destroy)Instance to
    // update our maps of VkDevices? Spec suggests no:
    // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/vkDestroyInstance.html
    // Valid Usage
    // All child objects created using instance
    // must have been destroyed prior to destroying instance
    //
    // This suggests that we should emulate the invalid behavior by
    // not destroying our own VkDevice maps on instance destruction.

    VkResult on_vkAllocateMemory(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkMemoryAllocateInfo* pAllocateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDeviceMemory* pMemory);

    void on_vkFreeMemory(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDeviceMemory memory,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkMapMemory(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDeviceMemory memory,
        VkDeviceSize offset,
        VkDeviceSize size,
        VkMemoryMapFlags flags,
        void** ppData);

    void on_vkUnmapMemory(
        android::base::BumpPool* pool,
        VkDevice device, VkDeviceMemory memory);

    uint8_t* getMappedHostPointer(VkDeviceMemory memory);
    VkDeviceSize getDeviceMemorySize(VkDeviceMemory memory);
    bool usingDirectMapping() const;

    struct HostFeatureSupport {
        bool supportsVulkan = false;
        bool supportsVulkan1_1 = false;
        bool supportsExternalMemory = false;
        bool useDeferredCommands = false;
        bool useCreateResourcesWithRequirements = false;
        uint32_t apiVersion = 0;
        uint32_t driverVersion = 0;
        uint32_t deviceID = 0;
        uint32_t vendorID = 0;
    };

    HostFeatureSupport getHostFeatureSupport() const;

    // VK_ANDROID_native_buffer
    VkResult on_vkGetSwapchainGrallocUsageANDROID(
        android::base::BumpPool* pool,
        VkDevice device,
        VkFormat format,
        VkImageUsageFlags imageUsage,
        int* grallocUsage);
    VkResult on_vkGetSwapchainGrallocUsage2ANDROID(
        android::base::BumpPool* pool,
        VkDevice device,
        VkFormat format,
        VkImageUsageFlags imageUsage,
        VkSwapchainImageUsageFlagsANDROID swapchainImageUsage,
        uint64_t* grallocConsumerUsage,
        uint64_t* grallocProducerUsage);
    VkResult on_vkAcquireImageANDROID(
        android::base::BumpPool* pool,
        VkDevice device,
        VkImage image,
        int nativeFenceFd,
        VkSemaphore semaphore,
        VkFence fence);
    VkResult on_vkQueueSignalReleaseImageANDROID(
        android::base::BumpPool* pool,
        VkQueue queue,
        uint32_t waitSemaphoreCount,
        const VkSemaphore* pWaitSemaphores,
        VkImage image,
        int* pNativeFenceFd);

    // VK_GOOGLE_gfxstream
    VkResult on_vkMapMemoryIntoAddressSpaceGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDeviceMemory memory,
        uint64_t* pAddress);
    VkResult on_vkGetMemoryHostAddressInfoGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDeviceMemory memory,
        uint64_t* pAddress,
        uint64_t* pSize,
        uint64_t* pHostmemId);

    // VK_GOOGLE_gfxstream
    VkResult on_vkFreeMemorySyncGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device,
        VkDeviceMemory memory,
        const VkAllocationCallbacks* pAllocator);

    // VK_GOOGLE_color_buffer
    VkResult on_vkRegisterImageColorBufferGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device, VkImage image, uint32_t colorBuffer);
    VkResult on_vkRegisterBufferColorBufferGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device, VkBuffer buffer, uint32_t colorBuffer);

    VkResult on_vkAllocateCommandBuffers(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkCommandBufferAllocateInfo* pAllocateInfo,
        VkCommandBuffer* pCommandBuffers);

    void on_vkCmdExecuteCommands(
        android::base::BumpPool* pool,
        VkCommandBuffer commandBuffer,
        uint32_t commandBufferCount,
        const VkCommandBuffer* pCommandBuffers);

    VkResult on_vkQueueSubmit(
        android::base::BumpPool* pool,
        VkQueue queue,
        uint32_t submitCount,
        const VkSubmitInfo* pSubmits,
        VkFence fence);

    VkResult on_vkQueueWaitIdle(
        android::base::BumpPool* pool,
        VkQueue queue);

    VkResult on_vkResetCommandBuffer(
        android::base::BumpPool* pool,
        VkCommandBuffer commandBuffer,
        VkCommandBufferResetFlags flags);

    void on_vkFreeCommandBuffers(
        android::base::BumpPool* pool,
        VkDevice device,
        VkCommandPool commandPool,
        uint32_t commandBufferCount,
        const VkCommandBuffer* pCommandBuffers);

    VkResult on_vkCreateCommandPool(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkCommandPoolCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkCommandPool* pCommandPool);

    void on_vkDestroyCommandPool(
        android::base::BumpPool* pool,
        VkDevice device,
        VkCommandPool commandPool,
        const VkAllocationCallbacks* pAllocator);

    VkResult on_vkResetCommandPool(
        android::base::BumpPool* pool,
        VkDevice device,
        VkCommandPool commandPool,
        VkCommandPoolResetFlags flags);

    void on_vkGetPhysicalDeviceExternalSemaphoreProperties(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
        VkExternalSemaphoreProperties* pExternalSemaphoreProperties);

    void on_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
        android::base::BumpPool* pool,
        VkPhysicalDevice physicalDevice,
        const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
        VkExternalSemaphoreProperties* pExternalSemaphoreProperties);

    VkResult on_vkCreateSemaphore(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkSemaphoreCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkSemaphore* pSemaphore);
    VkResult on_vkImportSemaphoreFdKHR(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo);
    VkResult on_vkGetSemaphoreFdKHR(
        android::base::BumpPool* pool,
        VkDevice boxed_device,
        const VkSemaphoreGetFdInfoKHR* pGetFdInfo,
        int* pFd);
    void on_vkDestroySemaphore(
        android::base::BumpPool* pool,
        VkDevice boxed_device,
        VkSemaphore semaphore,
        const VkAllocationCallbacks* pAllocator);

    // Descriptor update templates
    VkResult on_vkCreateDescriptorUpdateTemplate(
        android::base::BumpPool* pool,
        VkDevice boxed_device,
        const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);

    VkResult on_vkCreateDescriptorUpdateTemplateKHR(
        android::base::BumpPool* pool,
        VkDevice boxed_device,
        const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);

    void on_vkDestroyDescriptorUpdateTemplate(
        android::base::BumpPool* pool,
        VkDevice boxed_device,
        VkDescriptorUpdateTemplate descriptorUpdateTemplate,
        const VkAllocationCallbacks* pAllocator);

    void on_vkDestroyDescriptorUpdateTemplateKHR(
        android::base::BumpPool* pool,
        VkDevice boxed_device,
        VkDescriptorUpdateTemplate descriptorUpdateTemplate,
        const VkAllocationCallbacks* pAllocator);

    void on_vkUpdateDescriptorSetWithTemplateSizedGOOGLE(
        android::base::BumpPool* pool,
        VkDevice boxed_device,
        VkDescriptorSet descriptorSet,
        VkDescriptorUpdateTemplate descriptorUpdateTemplate,
        uint32_t imageInfoCount,
        uint32_t bufferInfoCount,
        uint32_t bufferViewCount,
        const uint32_t* pImageInfoEntryIndices,
        const uint32_t* pBufferInfoEntryIndices,
        const uint32_t* pBufferViewEntryIndices,
        const VkDescriptorImageInfo* pImageInfos,
        const VkDescriptorBufferInfo* pBufferInfos,
        const VkBufferView* pBufferViews);

    VkResult on_vkBeginCommandBuffer(
            android::base::BumpPool* pool,
            VkCommandBuffer commandBuffer,
            const VkCommandBufferBeginInfo* pBeginInfo);
    void on_vkBeginCommandBufferAsyncGOOGLE(
        android::base::BumpPool* pool,
        VkCommandBuffer commandBuffer,
        const VkCommandBufferBeginInfo* pBeginInfo);
    void on_vkEndCommandBufferAsyncGOOGLE(
        android::base::BumpPool* pool,
        VkCommandBuffer commandBuffer);
    void on_vkResetCommandBufferAsyncGOOGLE(
        android::base::BumpPool* pool,
        VkCommandBuffer commandBuffer,
        VkCommandBufferResetFlags flags);
    void on_vkCommandBufferHostSyncGOOGLE(
        android::base::BumpPool* pool,
        VkCommandBuffer commandBuffer,
        uint32_t needHostSync,
        uint32_t sequenceNumber);

    VkResult on_vkCreateImageWithRequirementsGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkImageCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkImage* pImage,
        VkMemoryRequirements* pMemoryRequirements);
    VkResult on_vkCreateBufferWithRequirementsGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device,
        const VkBufferCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkBuffer* pBuffer,
        VkMemoryRequirements* pMemoryRequirements);

    void on_vkCmdBindPipeline(android::base::BumpPool* pool,
                              VkCommandBuffer commandBuffer,
                              VkPipelineBindPoint pipelineBindPoint,
                              VkPipeline pipeline);

    void on_vkCmdBindDescriptorSets(android::base::BumpPool* pool,
                                    VkCommandBuffer commandBuffer,
                                    VkPipelineBindPoint pipelineBindPoint,
                                    VkPipelineLayout layout,
                                    uint32_t firstSet,
                                    uint32_t descriptorSetCount,
                                    const VkDescriptorSet* pDescriptorSets,
                                    uint32_t dynamicOffsetCount,
                                    const uint32_t* pDynamicOffsets);

    VkResult on_vkCreateRenderPass(android::base::BumpPool* pool,
                                   VkDevice device,
                                   const VkRenderPassCreateInfo* pCreateInfo,
                                   const VkAllocationCallbacks* pAllocator,
                                   VkRenderPass* pRenderPass);

    // VK_GOOGLE_gfxstream
    void on_vkQueueHostSyncGOOGLE(
        android::base::BumpPool* pool,
        VkQueue queue,
        uint32_t needHostSync,
        uint32_t sequenceNumber);
    void on_vkQueueSubmitAsyncGOOGLE(
        android::base::BumpPool* pool,
        VkQueue queue,
        uint32_t submitCount,
        const VkSubmitInfo* pSubmits,
        VkFence fence);
    void on_vkQueueWaitIdleAsyncGOOGLE(
        android::base::BumpPool* pool,
        VkQueue queue);
    void on_vkQueueBindSparseAsyncGOOGLE(
        android::base::BumpPool* pool,
        VkQueue queue,
        uint32_t bindInfoCount,
        const VkBindSparseInfo* pBindInfo, VkFence fence);

    // VK_GOOGLE_gfxstream
    void on_vkGetLinearImageLayoutGOOGLE(
        android::base::BumpPool* pool,
        VkDevice device,
        VkFormat format,
        VkDeviceSize* pOffset,
        VkDeviceSize* pRowPitchAlignment);

    // VK_GOOGLE_gfxstream
    void on_vkQueueFlushCommandsGOOGLE(
        android::base::BumpPool* pool,
        VkQueue queue,
        VkCommandBuffer commandBuffer,
        VkDeviceSize dataSize,
        const void* pData);

    // Transformations
    void deviceMemoryTransform_tohost(
        VkDeviceMemory* memory, uint32_t memoryCount,
        VkDeviceSize* offset, uint32_t offsetCount,
        VkDeviceSize* size, uint32_t sizeCount,
        uint32_t* typeIndex, uint32_t typeIndexCount,
        uint32_t* typeBits, uint32_t typeBitsCount);
    void deviceMemoryTransform_fromhost(
        VkDeviceMemory* memory, uint32_t memoryCount,
        VkDeviceSize* offset, uint32_t offsetCount,
        VkDeviceSize* size, uint32_t sizeCount,
        uint32_t* typeIndex, uint32_t typeIndexCount,
        uint32_t* typeBits, uint32_t typeBitsCount);

    // Snapshot access
    VkDecoderSnapshot* snapshot();

#define DEFINE_TRANSFORMED_TYPE_PROTOTYPE(type) \
    void transformImpl_##type##_tohost(const type*, uint32_t); \
    void transformImpl_##type##_fromhost(const type*, uint32_t); \
    
LIST_TRANSFORMED_TYPES(DEFINE_TRANSFORMED_TYPE_PROTOTYPE)

    // boxed handles
#define DEFINE_BOXED_DISPATCHABLE_HANDLE_API_DECL(type) \
    type new_boxed_##type(type underlying, VulkanDispatch* dispatch, bool ownDispatch); \
    void delete_##type(type boxed); \
    type unbox_##type(type boxed); \
    type unboxed_to_boxed_##type(type boxed); \
    VulkanDispatch* dispatch_##type(type boxed); \

#define DEFINE_BOXED_NON_DISPATCHABLE_HANDLE_API_DECL(type) \
    type new_boxed_non_dispatchable_##type(type underlying); \
    void delete_##type(type boxed); \
    type unbox_##type(type boxed); \
    type unboxed_to_boxed_non_dispatchable_##type(type boxed); \

GOLDFISH_VK_LIST_DISPATCHABLE_HANDLE_TYPES(DEFINE_BOXED_DISPATCHABLE_HANDLE_API_DECL)
GOLDFISH_VK_LIST_NON_DISPATCHABLE_HANDLE_TYPES(DEFINE_BOXED_NON_DISPATCHABLE_HANDLE_API_DECL)

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

#define MAKE_HANDLE_MAPPING_FOREACH(type_name, map_impl, map_to_u64_impl, map_from_u64_impl) \
    void mapHandles_##type_name(type_name* handles, size_t count) override { \
        for (size_t i = 0; i < count; ++i) { \
            map_impl; \
        } \
    } \
    void mapHandles_##type_name##_u64(const type_name* handles, uint64_t* handle_u64s, size_t count) override { \
        for (size_t i = 0; i < count; ++i) { \
            map_to_u64_impl; \
        } \
    } \
    void mapHandles_u64_##type_name(const uint64_t* handle_u64s, type_name* handles, size_t count) override { \
        for (size_t i = 0; i < count; ++i) { \
            map_from_u64_impl; \
        } \
    } \

#define BOXED_DISPATCHABLE_UNWRAP_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        if (handles[i]) { handles[i] = m_state->unbox_##type_name(handles[i]); } else { handles[i] = nullptr; } ;, \
        if (handles[i]) { handle_u64s[i] = (uint64_t)m_state->unbox_##type_name(handles[i]); } else { handle_u64s[i] = 0; }, \
        if (handle_u64s[i]) { handles[i] = m_state->unbox_##type_name((type_name)(uintptr_t)handle_u64s[i]); } else { handles[i] = nullptr; })

#define BOXED_NON_DISPATCHABLE_UNWRAP_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        if (handles[i]) { handles[i] = m_state->unbox_##type_name(handles[i]); } else { handles[i] = nullptr; } ;, \
        if (handles[i]) { handle_u64s[i] = (uint64_t)m_state->unbox_##type_name(handles[i]); } else { handle_u64s[i] = 0; }, \
        if (handle_u64s[i]) { handles[i] = m_state->unbox_##type_name((type_name)(uintptr_t)handle_u64s[i]); } else { handles[i] = nullptr; })

class BoxedHandleUnwrapMapping : public VulkanHandleMapping {
public:
    BoxedHandleUnwrapMapping(VkDecoderGlobalState* state) : VulkanHandleMapping(state) { }
    virtual ~BoxedHandleUnwrapMapping() { }
    GOLDFISH_VK_LIST_DISPATCHABLE_HANDLE_TYPES(BOXED_DISPATCHABLE_UNWRAP_IMPL)
    GOLDFISH_VK_LIST_NON_DISPATCHABLE_HANDLE_TYPES(BOXED_NON_DISPATCHABLE_UNWRAP_IMPL)
};

#define BOXED_DISPATCHABLE_WRAP_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        if (handles[i]) { handles[i] = m_state->unboxed_to_boxed_##type_name(handles[i]); } else { handles[i] = nullptr; } ;, \
        if (handles[i]) { handle_u64s[i] = (uint64_t)m_state->unboxed_to_boxed_##type_name(handles[i]); } else { handle_u64s[i] = 0; }, \
        if (handle_u64s[i]) { handles[i] = m_state->unboxed_to_boxed_##type_name((type_name)(uintptr_t)handle_u64s[i]); } else { handles[i] = nullptr; })

#define BOXED_NON_DISPATCHABLE_WRAP_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        if (handles[i]) { handles[i] = m_state->unboxed_to_boxed_non_dispatchable_##type_name(handles[i]); } else { handles[i] = nullptr; } ;, \
        if (handles[i]) { handle_u64s[i] = (uint64_t)m_state->unboxed_to_boxed_non_dispatchable_##type_name(handles[i]); } else { handle_u64s[i] = 0; }, \
        if (handle_u64s[i]) { handles[i] = m_state->unboxed_to_boxed_non_dispatchable_##type_name((type_name)(uintptr_t)handle_u64s[i]); } else { handles[i] = nullptr; })

class BoxedHandleWrapMapping : public VulkanHandleMapping {
public:
    BoxedHandleWrapMapping(VkDecoderGlobalState* state) : VulkanHandleMapping(state) { }
    virtual ~BoxedHandleWrapMapping() { }
    GOLDFISH_VK_LIST_DISPATCHABLE_HANDLE_TYPES(BOXED_DISPATCHABLE_WRAP_IMPL)
    GOLDFISH_VK_LIST_NON_DISPATCHABLE_HANDLE_TYPES(BOXED_NON_DISPATCHABLE_WRAP_IMPL)
};

// Not used, so we do not define.
#define BOXED_DISPATCHABLE_CREATE_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        (void)handles[i], \
        (void)handle_u64s[i], \
        (void)handles[i];)

// Not used, so we do not define.
#define BOXED_DISPATCHABLE_DESTROY_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        (void)handles[i], \
        (void)handle_u64s[i], \
        (void)handles[i];)

// We only use the create/destroy mappings for non dispatchable handles.
#define BOXED_NON_DISPATCHABLE_CREATE_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        handles[i] = new_boxed_non_dispatchable_##type_name(handles[i]);, \
        handle_u64s[i] = (uint64_t)new_boxed_non_dispatchable_##type_name(handles[i]), \
        handles[i] = (type_name)new_boxed_non_dispatchable_##type_name((type_name)(uintptr_t)handle_u64s[i]);)

#define BOXED_NON_DISPATCHABLE_DESTROY_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        delete_##type_name(handles[i]), \
        (void)handle_u64s[i]; delete_##type_name(handles[i]), \
        (void)handles[i]; delete_##type_name((type_name)handle_u64s[i]))

#define BOXED_NON_DISPATCHABLE_UNWRAP_AND_DELETE_IMPL(type_name) \
    MAKE_HANDLE_MAPPING_FOREACH(type_name, \
        if (handles[i]) { auto boxed = handles[i]; handles[i] = m_state->unbox_##type_name(handles[i]); delete_##type_name(boxed); } else { handles[i] = nullptr; } ;, \
        if (handles[i]) { auto boxed = handles[i]; handle_u64s[i] = (uint64_t)m_state->unbox_##type_name(handles[i]); delete_##type_name(boxed); } else { handle_u64s[i] = 0; }, \
        if (handle_u64s[i]) { auto boxed = (type_name)(uintptr_t)handle_u64s[i]; handles[i] = m_state->unbox_##type_name((type_name)(uintptr_t)handle_u64s[i]); delete_##type_name(boxed); } else { handles[i] = nullptr; })

class BoxedHandleCreateMapping : public VulkanHandleMapping {
public:
    BoxedHandleCreateMapping(VkDecoderGlobalState* state) : VulkanHandleMapping(state) { }
    virtual ~BoxedHandleCreateMapping() { }
    GOLDFISH_VK_LIST_DISPATCHABLE_HANDLE_TYPES(BOXED_DISPATCHABLE_CREATE_IMPL)
    GOLDFISH_VK_LIST_NON_DISPATCHABLE_HANDLE_TYPES(BOXED_NON_DISPATCHABLE_CREATE_IMPL)
};

class BoxedHandleDestroyMapping : public VulkanHandleMapping {
public:
    BoxedHandleDestroyMapping(VkDecoderGlobalState* state) : VulkanHandleMapping(state) { }
    virtual ~BoxedHandleDestroyMapping() { }
    GOLDFISH_VK_LIST_DISPATCHABLE_HANDLE_TYPES(BOXED_DISPATCHABLE_DESTROY_IMPL)
    GOLDFISH_VK_LIST_NON_DISPATCHABLE_HANDLE_TYPES(BOXED_NON_DISPATCHABLE_DESTROY_IMPL)
};

class BoxedHandleUnwrapAndDeleteMapping : public VulkanHandleMapping {
public:
    BoxedHandleUnwrapAndDeleteMapping(VkDecoderGlobalState* state) : VulkanHandleMapping(state) { }
    virtual ~BoxedHandleUnwrapAndDeleteMapping() { }
    GOLDFISH_VK_LIST_DISPATCHABLE_HANDLE_TYPES(BOXED_DISPATCHABLE_DESTROY_IMPL)
    GOLDFISH_VK_LIST_NON_DISPATCHABLE_HANDLE_TYPES(BOXED_NON_DISPATCHABLE_UNWRAP_AND_DELETE_IMPL)
};

#define HANDLE_MAPPING_DECLS(type_name) \
    void mapHandles_##type_name(type_name* handles, size_t count) override; \
    void mapHandles_##type_name##_u64(const type_name* handles, uint64_t* handle_u64s, size_t count) override; \
    void mapHandles_u64_##type_name(const uint64_t* handle_u64s, type_name* handles, size_t count) override; \

class BoxedHandleUnwrapAndDeletePreserveBoxedMapping : public VulkanHandleMapping {
public:
    BoxedHandleUnwrapAndDeletePreserveBoxedMapping(VkDecoderGlobalState* state) : VulkanHandleMapping(state) { }
    void setup(android::base::BumpPool* pool, uint64_t** bufPtr);
    virtual ~BoxedHandleUnwrapAndDeletePreserveBoxedMapping() { }

    GOLDFISH_VK_LIST_DISPATCHABLE_HANDLE_TYPES(HANDLE_MAPPING_DECLS)
    GOLDFISH_VK_LIST_NON_DISPATCHABLE_HANDLE_TYPES(HANDLE_MAPPING_DECLS)

private:
    void allocPreserve(size_t count);

    android::base::BumpPool* mPool = nullptr;
    uint64_t** mPreserveBufPtr = nullptr;
};

} // namespace goldfish_vk
